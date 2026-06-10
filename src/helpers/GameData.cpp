#include "GameData.h"
#include "SpaceshipGame.h"
#include <memory.h>

GameData::GameData()
{}

GameData::~GameData()
{ if(!shuttingDown) { error("Shutdown not called"); }}

void GameData::Shutdown(SpaceshipGame* game)
{
	shuttingDown = true;
	Reset(game);
}

void GameData::Reset(SpaceshipGame* game){
	//delete
	int n = spaceShips.size();
	for(int i = 0; i < n; i++)
    {
		if(spaceShips[i] != nullptr && !spaceShips[i]->deleted)
		{
			if(spaceShips[i]->entity.GetComponent<SpaceshipData>(game).isAlive)
			{
				game->KillSpaceship(spaceShips[i]);
			}
		}
    }
    spaceShips.clear();
	n = asteroids.size();
	for(int i = 0; i < n; i++)
    {
		game->DestroyEntity(asteroids[i]);
	}
    asteroids.clear();
	
	if(cubemapEntity && !cubemapEntity->deleted) game->DestroyEntity(cubemapEntity);
	if(cameraUsed && !cameraUsed->deleted) game->DestroyEntity(cameraUsed);
	
	if(cockpitEntity && !cockpitEntity->deleted) game->DestroyEntity(cockpitEntity);    
	if(posTextEntity && !posTextEntity->deleted) game->DestroyEntity(posTextEntity);
	if(throttleTextEntity && !throttleTextEntity->deleted) game->DestroyEntity(throttleTextEntity);
	if(instrumentEntity && !instrumentEntity->deleted) game->DestroyEntity(instrumentEntity);
	if(indicatorEntity && !indicatorEntity->deleted) game->DestroyEntity(indicatorEntity);
	
	//reset
	exitingLevel = false;
	
	if(physicsSystem) physicsSystem.reset();
	
	/**PLAYER INFO**/
	playerId = -1;
	viewpointType = ViewpointTypes::ThirdPerson; 
}

void GameData::GameTickUpdate(SpaceshipGame* game, const InputSystem& inputSystem)
{
	/********WINDOW_CONTROLLS*******/
	if(inputSystem.IsKeyDown(ESCAPE_KEY))
	{
		game->ToggleCursor();
	}
	if(inputSystem.IsKeyDown(VIEWPOINT_CHANGE))
	{
		if(viewpointType == ViewpointTypes::ThirdPerson)
		{
			viewpointType = ViewpointTypes::FirstPerson;
		} else 
		{
			viewpointType = ViewpointTypes::ThirdPerson;
		}
	}

	/********GAME_LOGIC*********/
	int n = asteroids.size();
    for (int i = 0; i < n; i++)
    {
        asteroids[i]->entity.GetComponent<AsteroidData>(game).Update(game, asteroids[i]);   
    }
	
	int liveEnemies = 0;
	n = spaceShips.size();
    bool stopGame = false;
    for(int i = 0; i < n; i++)
    {
		SpaceshipData& data = spaceShips[i]->entity.GetComponent<SpaceshipData>(game);
        if(data.isAlive)
        {
            data.Update(inputSystem, game, spaceShips[i]);
         
			if(!data.isPlayer) { liveEnemies++; }
			else { 
				Transform& transform = cameraUsed->entity.GetComponent<Transform>(game);
				Transform& player_transform = spaceShips[i]->entity.GetComponent<Transform>(game);
				
				//player_transform.forward = {1.0, 0.0, 1.0}; 
				//player_transform.right = {-1.0, 0.0, 1.0}; 
				//player_transform.up = {0.0, 1.0, 0.0}; 
				transform.position = player_transform.position; 
				transform.forward = player_transform.forward; 
				transform.right = player_transform.right; 
				transform.up = player_transform.up; 
				if(viewpointType == ViewpointTypes::ThirdPerson)
				{
					transform.Move(transform.forward * -2);
					transform.Move(transform.up * 1);
				} 
				
				//transform.Move(transform.up.Normalized() * 0.4);
				transform.UpdateTransformationMatrix();
				//transform.position = {-5.0, 0.0, 4.0};
				//player_transform.position = {-4.0, 0.0, 5.0};
				//player_transform.UpdateTransformationMatrix();
			}
        }
    }
	
	if(liveEnemies == 0)
    {
		spaceShips.push_back(std::make_shared<EntityHandle>());
		game->InitEnemy(spaceShips[spaceShips.size() - 1]);
		//TODO
        //spaceShips.emplace_back(std::make_shared<Spaceship>(currentNextId++, assetLoader->meshes[0], d3ObjectShaders, *glResLib, *physicsSystem));
    }
	physicsSystem->CheckCollisions(game);
}

void GameData::GameRenderUpdate(SpaceshipGame* game, const InputSystem& inputSystem)
{
	/********RENDER*****************/
	game->renderer->Render(cubemapEntity);
	int n = spaceShips.size();
    for(int i = 0; i < n; i++)
    {
		SpaceshipData& data = spaceShips[i]->entity.GetComponent<SpaceshipData>(game);
		if(data.isPlayer && viewpointType == ViewpointTypes::FirstPerson) 
		{
			continue; 
		}	
	
		game->renderer->Render(spaceShips[i]);
	}
	n = asteroids.size();
    for(int i = 0; i < n; i++)
    {
		game->renderer->Render(asteroids[i]);
	}
	if(viewpointType == ViewpointTypes::FirstPerson)
	{	
		Transform& transform = spaceShips[playerId]->entity.GetComponent<Transform>(game);
		SpaceshipData& spaceShipData = spaceShips[playerId]->entity.GetComponent<SpaceshipData>(game);
		
		game->SetText(throttleTextEntity->entity.GetComponent<TextData>(game), std::string("THRTL: ") + std::to_string(spaceShipData.throttle), 28);
		game->SetText(posTextEntity->entity.GetComponent<TextData>(game), std::string("POS: ") + transform.position.ToString(), 28);
		game->renderer->Render(throttleTextEntity);
		game->renderer->Render(posTextEntity);
		game->renderer->Render(instrumentEntity);
		game->renderer->Render(indicatorEntity);
		game->renderer->Render(cockpitEntity);
	}
}