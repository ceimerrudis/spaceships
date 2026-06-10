#pragma once
#include "GlobalInclude.h"
#include "cat/cat.h"
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include <array>
#include "SpaceshipData.h"
#include "Collider.h"
#include "PhysicsSystem.h"
#include "ViewpointTypes.h"
#include "AsteroidData.h"
#include "GameState.h"
#include "GameData.h"
#include "Constantes.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::shared_ptr;
using std::vector;
using cat::EntityHandle;

class SpaceshipGame : public cat::Game {
public:
	GameState gameState = GameState::Menu;
	GameData gameData;
	
	uint64_t mechanicalFontAssetId;
	uint64_t motomangFontAssetId;
	
	uint64_t cubeAssetId;
	uint64_t cubeMapAssetId;
	uint64_t spacehipAssetId;
	uint64_t asteroidAssetId;
	
	uint64_t skyboxImageRight;   
	uint64_t skyboxImageLeft;    
	uint64_t skyboxImageTop; 
	uint64_t skyboxImageBottom;
	uint64_t skyboxImageFarRight;
	uint64_t skyboxImageMiddle;
	
	uint64_t cockpitImage;
	uint64_t instrumentImage; 
	uint64_t indicatorImage;  
	
	void StartLevel();
	
	void CloseLevel();
	
	void InitGame();
	
	void InitCamera(shared_ptr<EntityHandle> cameraEntity);
	
	void InitPlayer(shared_ptr<EntityHandle> playerEntity);

	void InitEnemy(shared_ptr<EntityHandle> enemyEntity);

	void InitSkybox(shared_ptr<EntityHandle> skyboxEntity);

	void InitCockpit(shared_ptr<EntityHandle> cockpitEntity, 
		shared_ptr<EntityHandle> throttleTextEntity,
		shared_ptr<EntityHandle> posTextEntity,
		shared_ptr<EntityHandle> instrumentEntity,
		shared_ptr<EntityHandle> indicatorEntity);
	
	void InitAsteroid(shared_ptr<EntityHandle> asteroidEntity);
	
	void InitKeybinds();
	

    SpaceshipGame();
   
    ~SpaceshipGame() override;

    void TickUpdate() override;
	
	void RenderUpdate() override;

    void ShootLaser(Ray fireRay);

    void KillSpaceship(shared_ptr<EntityHandle>& entity);
	
	virtual void OnScreenResize(cat::Vector<int, 2> newScreenSize, int WorldPixelScale, int UIPixelScale) override;

};
