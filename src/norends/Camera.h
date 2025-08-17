#pragma once
#include "GlobalInclude.h"
#include "WorldObject.h"
#include "AdvancedMath.h"
#include "Spaceship.h"
#include "Renderer.h"

struct Camera: public WorldObject {
    //Iegūst matricu lai pārietu  no pasaules koordinātēm uz novērotāja koordinātēm
    matrix4 projectionMatrix;
    Spaceship* spaceship;
    std::unique_ptr<TextObject> throttleText;
    std::unique_ptr<TextObject> RotText;
    std::unique_ptr<TextObject>  PosText;
    std::unique_ptr<CubemapObject>  skybox;
    std::unique_ptr<D2Object>  cockpit;
    matrix4 WorldToObserverSpaceMatrix();

    void Render(Renderer& renderer, std::weak_ptr<TextureManager> textureManager);

    Camera(Spaceship* spaceship);

    ~Camera();
};