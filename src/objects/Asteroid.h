#pragma once
#include "GlobalInclude.h"
#include <glad/glad.h>
#include "ObjectLoader.h"
#include "InputSystem.h"
#include "Collider.h"
#include "MeshData.h"
#include "PhysicsSystem.h"
#include <memory>
#include "Entity.h"
#include "Shading.h"
#include "Transform.h"

class Game;

struct Asteroid
{
    Entity entity;
    Renderable renderable;
    Shading shading;
    Transform transform;
    MeshData meshData;

    float* vertexes;
    unsigned int* indices;
    unsigned int id;

    Asteroid(unsigned int id, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib, PhysicsSystem& physSys);

    void update(Game* game);

    ~Asteroid();

    static std::shared_ptr<solar::Mesh> GenAsteroid(unsigned int id);
};
