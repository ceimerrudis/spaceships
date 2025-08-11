#include "InputSystem.h"

void InputSystem::Update(GLFWwindow* window)
{
    int n = inputs.size();
    for (int i = 0; i < n; i++)
    {
        if(inputs[i].keycode > GLFW_KEY_LAST)
        {
            int btn;
            if(inputs[i].keycode == KEY_MOUSE_ONE)
            {
                btn = GLFW_MOUSE_BUTTON_LEFT;
            }
            if(inputs[i].keycode == KEY_MOUSE_TWO)
            {
                btn = GLFW_MOUSE_BUTTON_RIGHT;
            }
            if(inputs[i].keycode == KEY_MOUSE_MIDDLE)
            {
                btn = GLFW_MOUSE_BUTTON_MIDDLE;
            }
            if(inputs[i].keycode == KEY_MOUSE_AD1)
            {
                btn = 3;
            }
            if(inputs[i].keycode == KEY_MOUSE_AD2)
            {
                btn = 4;
            }
            inputs[i].state = glfwGetMouseButton(window, btn);    
        }
        else
        {
            inputs[i].state = 0;
            if (glfwGetKey(window, inputs[i].keycode) == GLFW_PRESS) 
            {
                inputs[i].state = 1;
            }
            if (glfwGetKey(window, inputs[i].keycode) == GLFW_REPEAT) 
            {
                inputs[i].state = 2;
            }
            if (glfwGetKey(window, inputs[i].keycode) == GLFW_RELEASE) 
            {
                inputs[i].state = 3;
            }
        }
    }
}

bool InputSystem::IsKeyPressed(unsigned int keyName)
{
    int n = inputs.size();
    for (int i = 0; i < n; i++)
    {
        if(keyName == inputs[i].keyname)
        {
            return (inputs[i].state == 1 || inputs[i].state == 2);
        }
    }
    return false;
}

bool InputSystem::IsKeyReleased(unsigned int keyName)
{
    int n = inputs.size();
    for (int i = 0; i < n; i++)
    {
        if(keyName == inputs[i].keyname)
        {
            return inputs[i].state == 3;
        }
    }
    return false;
}

InputSystem::InputSystem()
{
    //Key mapping
    Input temp;
    temp.state = 0;
    temp.keyname = ROLL_CLOCKWISE_KEY;
    temp.keycode = GLFW_KEY_SPACE;
    inputs.push_back(temp);
    temp.keyname = ROLL_CCLOCKWISE_KEY;
    temp.keycode = GLFW_KEY_LEFT_SHIFT;
    inputs.push_back(temp);
    temp.keyname = YAW_LEFT_KEY;
    temp.keycode = GLFW_KEY_A;
    inputs.push_back(temp);
    temp.keyname = YAW_RIGHT_KEY;
    temp.keycode = GLFW_KEY_D;
    inputs.push_back(temp);
    temp.keyname = PITCH_DOWN_KEY;
    temp.keycode = GLFW_KEY_S;
    inputs.push_back(temp);
    temp.keyname = PITCH_UP_KEY;
    temp.keycode = GLFW_KEY_W;
    inputs.push_back(temp);
    temp.keyname = THROTTLE_DOWN_KEY;
    temp.keycode = GLFW_KEY_Q;
    inputs.push_back(temp);
    temp.keyname = THROTTLE_UP_KEY;
    temp.keycode = GLFW_KEY_E;
    inputs.push_back(temp);

    temp.keyname = FIRE_KEY;
    temp.keycode = KEY_MOUSE_ONE;
    inputs.push_back(temp);
}