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
{
    entity.ID = id;
    InitTransform(transform);
    InitSpaceshipData(spaceshipData);
    InitRenderable(renderable, shaders,  glResLib);
    InitMeshData(meshData, renderable, mesh);
    InitShading(shading, renderable, meshData, glResLib);
    physSys.AddCollider(id, transform.position, Vector<float, 3>{1.0f, 1.0f, 1.0f});
}

void Spaceship::update(InputSystem& inputSystem, Game* game)
{
    if(spaceshipData.isPlayer)
    {
        spaceshipData.aiThrottle = 0;
        spaceshipData.aiFire = 0;
        spaceshipData.aiYaw = 0;
        spaceshipData.aiRoll = 0;
        spaceshipData.aiPitch = 0;
        spaceshipData.aiMoveRight = 0;
        spaceshipData.aiMoveUp = 0;
        spaceshipData.aiBreaks = 0;
        
        if(inputSystem.IsKeyHeld(BREAK_KEY)){ spaceshipData.aiBreaks = 1;}
        
        if(inputSystem.IsKeyHeld(FIRE_KEY)){ spaceshipData.aiFire = 1;}

        if(inputSystem.IsKeyHeld(THROTTLE_UP_KEY)){ spaceshipData.aiThrottle += 1;}
        if(inputSystem.IsKeyHeld(THROTTLE_DOWN_KEY)){ spaceshipData.aiThrottle -= 1;}

        if(inputSystem.IsKeyHeld(YAW_RIGHT_KEY)){ spaceshipData.aiRoll += 1;}
        if(inputSystem.IsKeyHeld(YAW_LEFT_KEY)){ spaceshipData.aiRoll -= 1;}
        
        if(inputSystem.IsKeyHeld(MOVE_RIGHT_KEY)){ spaceshipData.aiMoveRight += 1;}
        if(inputSystem.IsKeyHeld(MOVE_LEFT_KEY)){ spaceshipData.aiMoveRight -= 1;}
        if(inputSystem.IsKeyHeld(MOVE_UP_KEY)){ spaceshipData.aiMoveUp += 1;}
        if(inputSystem.IsKeyHeld(MOVE_DOWN_KEY)){ spaceshipData.aiMoveUp -= 1;}

        inputSystem.GetMouseDelta(&spaceshipData.aiYaw, &spaceshipData.aiPitch);
        spaceshipData.aiYaw  = clamp(spaceshipData.aiYaw, -20, 20);
        spaceshipData.aiPitch = clamp(spaceshipData.aiPitch, -20, 20);
    }
    else{
        //ai
        spaceshipData.throttle = 10;
        if(spaceshipData.commandCooldown == 0)
        {
            spaceshipData.aiYaw = RandomNegZeroPos();
            spaceshipData.aiRoll = RandomNegZeroPos();
            spaceshipData.aiPitch = RandomNegZeroPos();
            
            spaceshipData.commandCooldown = spaceshipData.COMMAND_COOLDOWN;
        }
        else
        {
            spaceshipData.commandCooldown--;
        }
    }
    
    spaceshipData.throttle += (spaceshipData.aiThrottle);
    if(spaceshipData.throttle > spaceshipData.MAX_THROTTLE)
    {
        spaceshipData.throttle = spaceshipData.MAX_THROTTLE;
    }
    if(spaceshipData.throttle < -spaceshipData.MAX_THROTTLE)
    {
        spaceshipData.throttle = -spaceshipData.MAX_THROTTLE;
    }

    Vector<float, 3> thrustDir = (transform.forward * 3) + transform.right*spaceshipData.aiMoveRight + transform.up*spaceshipData.aiMoveUp;
    
    spaceshipData.physicsData.AddVelocity(thrustDir.Normalized(), float(spaceshipData.throttle) / 80000);
    
    spaceshipData.physicsData.AddAngularVelocity(transform.up, spaceshipData.aiYaw / -40);
    spaceshipData.physicsData.AddAngularVelocity(transform.forward, spaceshipData.aiRoll / 70);
    spaceshipData.physicsData.AddAngularVelocity(transform.right, spaceshipData.aiPitch / 40);
    //Rotate(up, aiYaw / -50);
    //Rotate(forward, aiRoll / 50);
    //Rotate(right, aiPitch / 50);
    
    spaceshipData.physicsData.AddAngularVelocity(spaceshipData.physicsData.angularVelocity.Normalized(), -0.001);
    
    if(spaceshipData.aiBreaks > 0)
    {
        spaceshipData.physicsData.AddVelocity(spaceshipData.physicsData.velocity, -0.5);
    }else
    {
        spaceshipData.physicsData.AddVelocity(spaceshipData.physicsData.velocity, -0.01);
    }

    Move(transform, spaceshipData.physicsData.velocity);
    Rotate(transform, spaceshipData.physicsData.angularVelocity.Normalized(), spaceshipData.physicsData.angularVelocity.Magnitude()/10);    

    if(spaceshipData.fireCooldown == 0)
    {
        if(spaceshipData.aiFire == 1){
            Ray laserFire = Ray{
                entity.ID,
                Vector<float, 3>{transform.position.x(), transform.position.y(), transform.position.z()},
                Vector<float, 3>{transform.forward.x(), transform.forward.y(), transform.forward.z()}
            };
            game->ShootLaser(laserFire);
            spaceshipData.fireCooldown = spaceshipData.FIRE_COOLDOWN;
        }
    }
    else
    {
        spaceshipData.fireCooldown--;
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