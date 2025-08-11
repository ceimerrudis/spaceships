#include "SpaceShip.h"
#include "glad/glad.h"
#include "GLerrorHandling.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include "ObjectLoader.h"
#include "InputSystem.h"

void Spaceship::die(){
    isAlive = false;
    delete[] normalIndexes;
}

matrix4 Spaceship::GetRotMatrix()
{
    matrix4 mat = translationMat;
    mat(0, 3) = 0;
    mat(1, 3) = 0;
    mat(2, 3) = 0;
    return mat;
}

Spaceship::Spaceship(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib)
:   ModelObject(mesh, shaders, glResLib)
{
    health = 20;
    maxThrottle = 150;
    throttle = 0;
    isAlive = true;
    isPlayer = false;
}

void Spaceship::update(InputSystem& inputSystem)
{
    int inpThrtl = 0;
    int yaw = 0;
    int roll = 0;
    int pitch = 0;
    int fire = 0;
    if(isPlayer)
    {
        if(inputSystem.IsKeyPressed(FIRE_KEY)){ fire = 1;}

        if(inputSystem.IsKeyPressed(THROTTLE_UP_KEY)){ inpThrtl += 1;}
        if(inputSystem.IsKeyPressed(THROTTLE_DOWN_KEY)){ inpThrtl -= 1;}

        if(inputSystem.IsKeyPressed(YAW_RIGHT_KEY)){ yaw += 1;}
        if(inputSystem.IsKeyPressed(YAW_LEFT_KEY)){ yaw -= 1;}
        
        if(inputSystem.IsKeyPressed(ROLL_CLOCKWISE_KEY)){ roll += 1;}
        if(inputSystem.IsKeyPressed(ROLL_CCLOCKWISE_KEY)){ roll -= 1;}
        
        if(inputSystem.IsKeyPressed(PITCH_UP_KEY)){ pitch += 1;}
        if(inputSystem.IsKeyPressed(PITCH_DOWN_KEY)){ pitch -= 1;}
    }
    else{
        //ai
        yaw = 1;
        throttle = 20;
    }
    
    throttle += (inpThrtl)*5;
    if(throttle > maxThrottle)
    {
        throttle = maxThrottle;
    }
    if(throttle < -maxThrottle)
    {
        throttle = -maxThrottle;
    }

    move(forward * (float(this->throttle) / -1000));
        
    rotate(up, (float)yaw / 50);
    rotate(forward, (float)roll / 50);
    rotate(right, (float)pitch / -50);
}