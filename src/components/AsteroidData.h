#pragma once
#include "cat/cat.h"

class SpaceshipGame;

class AsteroidData{
public:
	int dummy;//dummy data
	AsteroidData();

    ~AsteroidData();

    void Update(SpaceshipGame* game, std::shared_ptr<cat::EntityHandle> asteroidEntity);
};
