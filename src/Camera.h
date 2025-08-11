#pragma once
#include "GlobalInclude.h"
#include "WorldObject.h"
#include "AdvancedMath.h"
#include "Spaceship.h"

struct Camera: public WorldObject {
    //Iegūst matricu lai pārietu  no pasaules koordinātēm uz novērotāja koordinātēm
    matrix4 projectionMatrix;
    Spaceship* spaceship;
    int throttleText;
    int skybox;
    int cockpit;
    matrix4 WorldToObserverSpaceMatrix();

    std::vector<Renderable*> children;

    void Render(vector2i screenSize);

    Camera(Spaceship* spaceship);

    ~Camera();
};