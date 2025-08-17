#include "SpaceShip.h"
#include "glad/glad.h"
#include "GLerrorHandling.h"
#include "Logger.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "ObjectLoader.h"
#include "InputSystem.h"
#include <random>

int RandomNegZeroPos();

float clamp(float value, float min, float max) 
{
    return std::max(min, std::min(max, value));
}

Spaceship::Spaceship(unsigned int id, const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib, PhysicsSystem& physSys)
:   ModelObject(mesh, shaders, glResLib),
    id(id)
{
    health = 20;
    throttle = 0;
    isAlive = true;
    isPlayer = false;
    fireCooldown = 0;
    commandCooldown = 0;
    aiThrottle = 0;
    aiFire = 0;
    aiYaw = 0;
    aiRoll = 0;
    aiPitch = 0;
    aiMoveRight = 0;
    aiMoveUp = 0;
    
    physSys.AddCollider(id, position, {1.0f, 1.0f, 1.0f});
}

void Spaceship::update(InputSystem& inputSystem, Game* game)
{
    if(isPlayer)
    {
        aiThrottle = 0;
        aiFire = 0;
        aiYaw = 0;
        aiRoll = 0;
        aiPitch = 0;
        aiMoveRight = 0;
        aiMoveUp = 0;
        
        if(inputSystem.IsKeyHeld(FIRE_KEY)){ aiFire = 1;}

        if(inputSystem.IsKeyHeld(THROTTLE_UP_KEY)){ aiThrottle += 1;}
        if(inputSystem.IsKeyHeld(THROTTLE_DOWN_KEY)){ aiThrottle -= 1;}

        if(inputSystem.IsKeyHeld(YAW_RIGHT_KEY)){ aiRoll += 1;}
        if(inputSystem.IsKeyHeld(YAW_LEFT_KEY)){ aiRoll -= 1;}
        
        if(inputSystem.IsKeyHeld(MOVE_RIGHT_KEY)){ aiMoveRight += 1;}
        if(inputSystem.IsKeyHeld(MOVE_LEFT_KEY)){ aiMoveRight -= 1;}
        if(inputSystem.IsKeyHeld(MOVE_UP_KEY)){ aiMoveUp += 1;}
        if(inputSystem.IsKeyHeld(MOVE_DOWN_KEY)){ aiMoveUp -= 1;}

        inputSystem.GetMouseDelta(&aiYaw, &aiPitch);
        aiYaw  = clamp(aiYaw, -10, 10);
        aiPitch = clamp(aiPitch, -10, 10);
    }
    else{
        //ai
        throttle = 60;
        if(commandCooldown == 0)
        {
            //aiYaw = RandomNegZeroPos();
            aiRoll = RandomNegZeroPos();
            //aiPitch = RandomNegZeroPos();
            
            commandCooldown = COMMAND_COOLDOWN;
        }
        else
        {
            commandCooldown--;
        }
    }
    
    throttle += (aiThrottle)*5;
    if(throttle > MAX_THROTTLE)
    {
        throttle = MAX_THROTTLE;
    }
    if(throttle < -MAX_THROTTLE)
    {
        throttle = -MAX_THROTTLE;
    }

    move(forward * (float(this->aiThrottle) / 1));
    move(right * (float(this->aiMoveRight) / 1));
    move(up * (float(this->aiMoveUp) / 1));
        
    rotate(up, aiYaw / -50);
    rotate(forward, aiRoll / 50);
    rotate(right, aiPitch / 50);

    if(fireCooldown == 0)
    {
        if(aiFire == 1){
            Ray laserFire = Ray{
                id,
                {position.x(), position.y(), position.z()},
                {forward.x(), forward.y(), forward.z()}
            };
            game->ShootLaser(laserFire);
            fireCooldown = FIRE_COOLDOWN;
        }
    }
    else
    {
        fireCooldown--;
    }
}

int RandomNegZeroPos()
{
    static std::random_device rd;
    static std::    mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(-1, 1); // Range: -1 to 1 inclusive
    return dist(gen);
}

Spaceship::~Spaceship()
{

}