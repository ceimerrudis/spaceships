#pragma once	
#include "cat/cat.h"

class SpaceshipGame;

class AsteroidData{
public:
	shared_ptr<cat::Mesh> mesh;
	
	AsteroidData();

    ~AsteroidData();

    void Update(SpaceshipGame* game, std::shared_ptr<cat::EntityHandle> asteroidEntity);
	
};
