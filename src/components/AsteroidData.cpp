#include "AsteroidData.h"
#include "SpaceshipGame.h"
#include "PhysicsSystem.h"
#include "SpaceshipGame.h"
#include "AsteroidGenerator.h"
#include "cat/cat.h"
#include <algorithm>
#include <map>

AsteroidData::AsteroidData()
{
	mesh = GenAsteroid(cat::Random::RandomI(100, 1000));
}

AsteroidData::~AsteroidData()
{
	
}

void AsteroidData::Update(SpaceshipGame* game, std::shared_ptr<cat::EntityHandle> asteroidEntity)
{
	cat::Transform& transform = asteroidEntity->entity.GetComponent<cat::Transform>(game);
	transform.Rotate(transform.up, 0.01);
    transform.Rotate(transform.forward, 0.005);
}
