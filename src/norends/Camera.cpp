#include "Camera.h"
#include "AdvancedMath.h"
#include "TextObject.h"
#include "Shader.h"
#include <array>

Camera::Camera(Spaceship* spaceship) : WorldObject()
{
    this->spaceship = spaceship;
}

Camera::~Camera() 
{
}
    
void Camera::Render(Renderer& renderer, std::weak_ptr<TextureManager> textureManager)
{
    position = spaceship->position;// + (spaceship->up * 10) + (spaceship->forward * -20);
    up = spaceship->up;
    forward = spaceship->right;
    right = spaceship->forward*-1;
    int thr = spaceship->throttle;
    throttleText->SetText(std::string("THRTL: ") + std::to_string(thr), textureManager);
    renderer.Render(throttleText.get());
    PosText->SetText(std::string("POS: ") + spaceship->position.ToString(), textureManager);
    renderer.Render(PosText.get());
    skybox->shaders->AssignDataToUniform(SKYBOX_VIEW_MATRIX, WorldToObserverSpaceMatrix().data);
    renderer.Render(skybox.get());
    
    Vector<float, 3> indicatorPos = (spaceship->forward*-1).Normalized();
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

    renderer.Render(indicator.get());


    renderer.Render(instrument.get());
    //renderer.Render(cockpit.get());
}

Matrix<float, 4> Camera::WorldToObserverSpaceMatrix()
{
    UpdateTransformationMatrix();
    return transformMatrix.Inverse();
}