#pragma once
#include "GlobalInclude.h"
#include "WorldObject.h"
#include "D3Object.h"
#include <glad/glad.h>
#include "ObjectLoader.h"
#include "ModelObject.h"
#include "InputSystem.h"
#include "Collider.h"
#include "PhysicsSystem.h"
#include "PhysicsData.h"
#include <memory>

class Game;

struct Spaceship: public ModelObject{
    const int MAX_THROTTLE = 150;
    const int COMMAND_COOLDOWN = 500;
    const int FIRE_COOLDOWN = 100;
    const unsigned int id;
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

    Spaceship(unsigned int id, const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders,
         OpenGLResourceLibrary& glResLib, PhysicsSystem& physSys);

    void update(InputSystem& inputSystem, Game* game);

    ~Spaceship() override;
};
