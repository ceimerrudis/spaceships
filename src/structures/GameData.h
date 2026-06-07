#pragma once
#include "cat/cat.h"
#include "PhysicsSystem.h"
#include "ViewpointTypes.h"
#include <memory>
#include <vector>

using namespace cat;

class GameData {
public:
	SpaceshipGame* game;//used in destructor
	
	shared_ptr<PhysicsSystem> physicsSystem;
    std::vector<shared_ptr<EntityHandle>> spaceShips;
    std::vector<shared_ptr<EntityHandle>> asteroids;
    
	/**PLAYER INFO**/
	int playerId;
	ViewpointTypes viewpointType; 
	shared_ptr<EntityHandle> cubemapEntity;
	shared_ptr<EntityHandle> cameraUsed;
	
	shared_ptr<EntityHandle> cockpitEntity;
	shared_ptr<EntityHandle> throttleTextEntity;
	shared_ptr<EntityHandle> posTextEntity;
	shared_ptr<EntityHandle> instrumentEntity;
	shared_ptr<EntityHandle> indicatorEntity;
	
	void GameUpdate(SpaceshipGame* game, const InputSystem& inputSystem);
	
	void Shutdown();
	
	GameData(SpaceshipGame* game);
	
	~GameData();
};
