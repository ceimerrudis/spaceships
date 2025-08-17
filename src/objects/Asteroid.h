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
#include <memory>

class Game;

struct Asteroid: public ModelObject{
    float* vertexes;
    unsigned int* indices;
    unsigned int id;

    Asteroid(unsigned int id, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib, PhysicsSystem& physSys);

    void update(Game* game);

    ~Asteroid() override;

    static std::shared_ptr<solar::Mesh> GenAsteroid(unsigned int id);
};
