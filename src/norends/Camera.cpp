#include "Camera.h"
#include "AdvancedMath.h"
#include "TextObject.h"
#include "Shader.h"
#include <array>

Camera::Camera(Spaceship* spaceship)
{
    InitTransform(transform);
    this->spaceship = spaceship;
}

Camera::~Camera() 
{
}
    
void Camera::Render(Renderer& renderer, std::weak_ptr<TextureManager> textureManager)
{
    transform.position = spaceship->transform.position;// + (spaceship->up * 10) + (spaceship->forward * -20);
    transform.up = spaceship->transform.up;
    transform.forward = spaceship->transform.right;
    transform.right = spaceship->transform.forward*-1;
    int thr = spaceship->spaceshipData.throttle;
    throttleText->SetText(std::string("THRTL: ") + std::to_string(thr), 28, textureManager);
    renderer.Render(throttleText->uiTransform, throttleText->renderable, throttleText->textData, throttleText->imageData);
    PosText->SetText(std::string("POS: ") + spaceship->transform.position.ToString(), 28, textureManager);
    renderer.Render(PosText->uiTransform, PosText->renderable, PosText->textData, PosText->imageData);
    skybox->renderable.shaders->AssignDataToUniform(SKYBOX_VIEW_MATRIX, WorldToObserverSpaceMatrix().data);
    renderer.Render(skybox->transform, skybox->renderable, skybox->modelTexture);
    
    Vector<float, 3> indicatorPos = (spaceship->transform.forward*-1).Normalized();
    if(indicatorPos.x() <= 0)
    {
        //behind
    }

    //xy = z y
    //float a = -0.1 + (indicatorPos.z() + 1.0f) * 0.5f * (0.1 + 0.1);
    //float b = -0.4 + (indicatorPos.y() + 1.0f) * 0.5f * (-0.4 + 0.6);
    //Vector<float, 2> BL = Vector<float, 2>{a - 0.01, b - 0.01};
    //Vector<float, 2> TR = Vector<float, 2>{a + 0.01, b + 0.01};
    //{-0.1, -0.6}
    //{0.1, -0.4}, 
    //{-0.02, -0.52}, Vector<float, 2>{0.02, -0.48}

    renderer.Render(indicator->uiTransform, indicator->renderable, indicator->imageData);
    renderer.Render(instrument->uiTransform, instrument->renderable, instrument->imageData);
    renderer.Render(cockpit->uiTransform, cockpit->renderable, cockpit->imageData);   
}

Matrix<float, 4> Camera::WorldToObserverSpaceMatrix()
{
    UpdateTransformationMatrix(transform);
    return transform.transformMatrix.Inverse();
}