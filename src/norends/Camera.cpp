#include "Camera.h"
#include "AdvancedMath.h"
#include "TextObject.h"
#include "Shader.h"
#include <Remotery.h>
#include <array>

Camera::Camera(Spaceship* spaceship) : WorldObject()
{
    this->spaceship = spaceship;
    projectionMatrix = CreateProjectionMatrix();
}

Camera::~Camera() 
{
}
    
void Camera::Render(Renderer& renderer, std::weak_ptr<TextureManager> textureManager)
{
    position = spaceship->position;// + (spaceship->up * 10) + (spaceship->forward * -20);
    up = spaceship->up;
    forward = spaceship->forward;
    right = spaceship->right;
    int thr = spaceship->throttle;
    throttleText->SetText(std::string("THRTL: ") + std::to_string(thr), textureManager);
    renderer.Render(throttleText.get());
    PosText->SetText(std::string("POS: ") + spaceship->position.ToString(), textureManager);
    renderer.Render(PosText.get());
    RotText->SetText(std::string("THRTL: ") + spaceship->forward.ToString(), textureManager);
    renderer.Render(RotText.get());
    skybox->shaders->AssignDataToUniform(SKYBOX_VIEW_MATRIX, WorldToObserverSpaceMatrix().data);
    renderer.Render(skybox.get());
    renderer.Render(cockpit.get());
}

matrix4 Camera::WorldToObserverSpaceMatrix()
{
    updateTranslationMat();
    return translationMat.Inverse();
}