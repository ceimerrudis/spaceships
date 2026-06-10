#pragma once
#include "cat/cat.h"
#include "PhysicsSystem.h"
#include "ViewpointTypes.h"
#include <memory>
#include <vector>

using namespace cat;

class GameData {
public:
	bool shuttingDown = false;
	bool exitingLevel = false;
	
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
	
	void GameTickUpdate(SpaceshipGame* game, const InputSystem& inputSystem);
	
	void GameRenderUpdate(SpaceshipGame* game, const InputSystem& inputSystem);
	
	void Reset(SpaceshipGame* game);
	
	void Shutdown(SpaceshipGame* game);
	
	GameData();
	
	~GameData();
};
