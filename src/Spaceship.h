#pragma once
#include "GlobalInclude.h"
#include "WorldObject.h"
#include "D3Object.h"
#include <glad/glad.h>
#include "ObjectLoader.h"
#include "ModelObject.h"
#include "InputSystem.h"
#include "Collider.h"
#include <memory>

struct Spaceship: public ModelObject{
    bool isAlive;
    bool isPlayer;
    int maxThrottle;
    int health;
    
    const std::shared_ptr<Collider> collider;

    int throttle;

    Spaceship(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib);

    matrix4 GetRotMatrix();

    void die();

    void update(InputSystem& inputSystem);
};
