#pragma once
#include "GlobalInclude.h"
#include "PhysicsData.h"

struct SpaceshipData 
{
    #if DEBUG
        bool initialized;
    #endif
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
    int aiMoveUp;
    int aiMoveRight;
};

void InitSpaceshipData(SpaceshipData& spaceshipData);
