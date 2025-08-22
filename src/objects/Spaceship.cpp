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
    
    physicsData.velocity = {0, 0, 0};
    physicsData.angularVelocity = {0, 0, 0};
    
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
        aiBreaks = 0;
        
        if(inputSystem.IsKeyHeld(BREAK_KEY)){ aiBreaks = 1;}
        
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
        throttle = 10;
        if(commandCooldown == 0)
        {
            aiYaw = RandomNegZeroPos();
            aiRoll = RandomNegZeroPos();
            aiPitch = RandomNegZeroPos();
            
            commandCooldown = COMMAND_COOLDOWN;
        }
        else
        {
            commandCooldown--;
        }
    }
    
    throttle += (aiThrottle);
    if(throttle > MAX_THROTTLE)
    {
        throttle = MAX_THROTTLE;
    }
    if(throttle < -MAX_THROTTLE)
    {
        throttle = -MAX_THROTTLE;
    }

    vector3 thrustDir = (forward * 10) + right + up;
    
    physicsData.AddVelocity(thrustDir.Normalized(), float(throttle) / 80000);
    
    //physicsData.AddAngularVelocity(up, aiYaw / -80);
    //physicsData.AddAngularVelocity(forward, aiRoll / 140);
    //physicsData.AddAngularVelocity(right, aiPitch / 80);
    rotate(up, aiYaw / -50);
    rotate(forward, aiRoll / 50);
    rotate(right, aiPitch / 50);
    
    //physicsData.AddAngularVelocity(physicsData.angularVelocity.Normalized(), -0.001);
    
    if(aiBreaks > 0)
    {
        physicsData.AddVelocity(physicsData.velocity, -0.5);
    }else
    {
        physicsData.AddVelocity(physicsData.velocity, -0.01);
    }
    
    move(physicsData.velocity);
    //rotate(physicsData.angularVelocity.Normalized(), physicsData.angularVelocity.magnitude());    
    

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