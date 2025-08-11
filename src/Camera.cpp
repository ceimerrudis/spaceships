#include "Camera.h"
#include "AdvancedMath.h"
#include "TextObject.h"
#include "Shader.h"
#include <array>
#include <Eigen/Dense>

Camera::Camera(Spaceship* spaceship) : WorldObject()
{
    this->spaceship = spaceship;
    projectionMatrix = CreateProjectionMatrix();
}

Camera::~Camera() 
{
   int n = children.size();
    for (int i = 0; i < n; i++)
    {
        delete children[i];
    }
}

void Camera::Render(vector2i screenSize)
{
    position = spaceship->position;
    up = spaceship->up;
    forward = spaceship->forward;
    right = spaceship->right;
    int thr = spaceship->throttle;
    dynamic_cast<TextObject*>(children[throttleText])->SetText(std::string("THRTL:") + std::to_string(spaceship->throttle));
    dynamic_cast<TextObject*>(children[throttleText])->screenSize = screenSize;
    children[skybox]->shaders->AssignDataToUniform(SKYBOX_VIEW_MATRIX, WorldToObserverSpaceMatrix().data);

    int n = children.size();
    for (int i = 0; i < n; i++)
    {
        children[i]->Render();
    }
}

matrix4 Camera::WorldToObserverSpaceMatrix()
{
    //float tx = -(right % position);
    //float ty = -(up % position);
    //float tz = (forward % position);  // Since we negated F earlier

    //matrix4 mat;
    updateTranslationMat();
    Eigen::Matrix4f result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result(row, col) = (float)translationMat(row, col);
        }
    }
    
    Eigen::Matrix4f inv = result.inverse();

    matrix4 m;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            m(row, col) = inv(row, col);
        }
    }
    //std::array<float, 4> temp;
    //temp = {right.x(), up.x(), -forward.x(), 0};
    //mat.set_row(0, temp.data());
    //temp = {right.y(), up.y(), -forward.y(), 0};
    //mat.set_row(1, temp.data());
    //temp = {right.z(), up.z(), -forward.z(), 0};
    //mat.set_row(2, temp.data());
    //temp = {tx,  ty,  tz, 1};
    //mat.set_row(3, temp.data());

    return m;
}