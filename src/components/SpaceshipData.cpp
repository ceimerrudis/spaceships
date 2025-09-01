#include "SpaceshipData.h"

void InitSpaceshipData(SpaceshipData& spaceshipData)
{
    #if DEBUG
        spaceshipData.initialized = true;
    #endif
    spaceshipData.health = 20;
    spaceshipData.throttle = 0;
    spaceshipData.isAlive = true;
    spaceshipData.isPlayer = false;
    spaceshipData.fireCooldown = 0;
    spaceshipData.commandCooldown = 0;
    spaceshipData.aiThrottle = 0;
    spaceshipData.aiFire = 0;
    spaceshipData.aiYaw = 0;
    spaceshipData.aiRoll = 0;
    spaceshipData.aiPitch = 0;
    spaceshipData.aiMoveRight = 0;
    spaceshipData.aiMoveForward = 0;
    spaceshipData.physicsData.velocity = Vector<float, 3>{0, 0, 0};
    spaceshipData.physicsData.angularVelocity = Vector<float, 3>{0, 0, 0};
}
