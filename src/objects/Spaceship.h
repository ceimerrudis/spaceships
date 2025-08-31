#pragma once
#include "GlobalInclude.h"
#include <glad/glad.h>
#include "ObjectLoader.h"
#include "InputSystem.h"
#include "Collider.h"
#include "PhysicsSystem.h"
#include "PhysicsData.h"
#include "Renderable.h"
#include "Transform.h"
#include "SpaceshipData.h"
#include "Shading.h"
#include "Entity.h"
#include <memory>
#include "MeshData.h"

class Game;

class Spaceship
{
public:
    Entity entity;
    MeshData meshData;
    Transform transform;
    Renderable renderable;
    SpaceshipData spaceshipData;
    Shading shading;

    Spaceship(unsigned int id, const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders,
         OpenGLResourceLibrary& glResLib, PhysicsSystem& physSys);

    void update(InputSystem& inputSystem, Game* game);

    ~Spaceship();
};
