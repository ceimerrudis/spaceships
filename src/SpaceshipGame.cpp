#include "SpaceshipGame.h"
#include "GameData.h"
#include <memory.h>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using namespace cat;

SpaceshipGame::SpaceshipGame() : 
Game(GameName, BaseScreenWidth, BaseScreenHeight, GameType::Game3D, false)
{
	CAT_LOG_FPS = false;
	TARGET_FPS = 60;
	TARGET_TPS = 60;
	DRAW_AFTER_MAX_X_UPDATES = 1;
	CAT_DEBUG_CULL_FACES = true;
	
	mechanicalFontAssetId = assetLoader->LoadFont("mechanical-font/Mechanical-g5Y5.otf");
    motomangFontAssetId =assetLoader->LoadFont("motomang-font/Motomangucode-p7Jj1.ttf");

	cubeAssetId = assetLoader->LoadObject("cube.obj");
	cubeMapAssetId = assetLoader->LoadObject("cubemap_cube.obj");
	spacehipAssetId = assetLoader->LoadObject("spaceship.obj", true);
	asteroidAssetId = assetLoader->LoadObject("asteroid1.obj", true);

	skyboxImageRight    = assetLoader->LoadImage("skybox2_c00.bmp");//right +x
    skyboxImageLeft     = assetLoader->LoadImage("skybox2_c01.bmp");//left -x
    skyboxImageTop      = assetLoader->LoadImage("skybox2_c02.bmp");//top +y
    skyboxImageBottom   = assetLoader->LoadImage("skybox2_c03.bmp");//bottom -y
    skyboxImageFarRight = assetLoader->LoadImage("skybox2_c05.bmp");//far_right +z
    skyboxImageMiddle   = assetLoader->LoadImage("skybox2_c04.bmp");//middle -z
	
	cockpitImage    = assetLoader->LoadImage("cockpit.png");
    instrumentImage = assetLoader->LoadImage("instrument.png");
    indicatorImage  = assetLoader->LoadImage("indicator.png");
	
	gameData.shuttingDown = true;//ONLY ON GAME START
	
	InitKeybinds();
}

void SpaceshipGame::RenderUpdate()
{
	if(gameState == GameState::Game)
	{
		if(gameData.exitingLevel)
		{
			CloseLevel();
			gameData.exitingLevel = false;
		}else
		{
			gameData.GameRenderUpdate(this, *inputSystem);
		}
	}
}

void SpaceshipGame::TickUpdate()
{
	if(inputSystem->IsKeyDown(QUIT_GAME))
	{
		quitingGame = true;
	}
	if(inputSystem->IsKeyDown(FULLSCREEN))
	{
		ToggleFullscreen();
	}
	if(inputSystem->IsKeyDown(20))
	{
		if(gameState == GameState::Menu)
		{
			StartLevel();
		} else 
		{
			CloseLevel();
		}
	}
	
	if(gameState == GameState::Game)
	{
		if(gameData.exitingLevel)
		{
			gameData.exitingLevel = false;
			CloseLevel();
		}else
		{
			gameData.GameTickUpdate(this, *inputSystem);
		}
	}
}

void SpaceshipGame::StartLevel()
{
	gameData.Reset(this);
	InitGame();
	gameState = GameState::Game;
}

void SpaceshipGame::CloseLevel()
{
	gameData.Reset(this);
	gameState = GameState::Menu;
}

void SpaceshipGame::OnScreenResize(Vector<int, 2> newScreenSize, int WorldPixelScale, int UIPixelScale) 
{
	Game::OnScreenResize(newScreenSize, WorldPixelScale, UIPixelScale);
	
	//gameData->cameraUsed->entity.GetComponent<CameraData>(this).RecalculateProjectionMatrix(newScreenSize.x(), newScreenSize.y(), 400);
}

SpaceshipGame::~SpaceshipGame()
{
	gameData.Shutdown(this);
}

void SpaceshipGame::ShootLaser(Ray fireRay)
{
    //physicsSystem->ShootLaser(fireRay, this);
}

void SpaceshipGame::KillSpaceship(shared_ptr<EntityHandle>& entity)
{
	SpaceshipData& shipToKill = entity->entity.GetComponent<SpaceshipData>(this);
    if(!shipToKill.isAlive)
    {
        return;
    }
    
    if(shipToKill.isPlayer)
    {
        LOG("Player dead!");
        gameData.exitingLevel = true;
    }
	
	DestroyEntity(entity);
	entity.reset();
}
