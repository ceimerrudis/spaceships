#pragma once
#include "cat/cat.h"
#include "GlobalInclude.h"
#include "PhysicsData.h"
#include "SpaceshipGame.h"

struct SpaceshipData 
{
    const int MAX_THROTTLE = 150;
    const int COMMAND_COOLDOWN = 500;
    const int FIRE_COOLDOWN = 100;
    PhysicsData physicsData;
    bool isAlive;
    bool isPlayer;
    int health;

    int commandCooldown;
    int fireCooldown;
    int throttle;

    int aiBreaks;
    float aiYaw;
    float aiRoll; 
    float aiPitch;
    int aiThrottle;
    int aiFire;
    int aiMoveForward;
    int aiMoveRight;
	
	SpaceshipData();
	
	void Update(const cat::InputSystem& inputSystem, cat::Game* game, std::shared_ptr<cat::EntityHandle> spacehipEntity);
	
};


