#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "Spaceship.h"
#include "Renderer.h"
#include "Image.h"

struct Camera 
{
    Transform transform;
    //Iegūst matricu lai pārietu  no pasaules koordinātēm uz novērotāja koordinātēm
    Matrix<float, 4> projectionMatrix;
    Spaceship* spaceship;
    std::unique_ptr<TextObject> throttleText;
    std::unique_ptr<TextObject>  PosText;
    std::unique_ptr<CubemapObject>  skybox;
    std::unique_ptr<Image>  cockpit;
    std::unique_ptr<Image>  instrument;
    std::unique_ptr<Image>  indicator;
    Matrix<float, 4> WorldToObserverSpaceMatrix();

    void Render(Renderer& renderer, std::weak_ptr<TextureManager> textureManager);

    Camera(Spaceship* spaceship);

    ~Camera();
};