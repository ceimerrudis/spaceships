#pragma once
#include "GlobalInclude.h"
#include <glad/glad.h>
#include "glfw3.h"
#include <vector>

//My own extension of opengl key list
#define KEY_MOUSE_ONE GLFW_KEY_LAST+1
#define KEY_MOUSE_TWO GLFW_KEY_LAST+2
#define KEY_MOUSE_MIDDLE GLFW_KEY_LAST+3
#define KEY_MOUSE_AD1 GLFW_KEY_LAST+4
#define KEY_MOUSE_AD2 GLFW_KEY_LAST+5

//keys used in game (friendly names)
#define PITCH_UP_KEY 1
#define PITCH_DOWN_KEY 2
#define YAW_LEFT_KEY 3
#define YAW_RIGHT_KEY 4
#define ROLL_CLOCKWISE_KEY 5
#define ROLL_CCLOCKWISE_KEY 6
#define THROTTLE_UP_KEY 7
#define THROTTLE_DOWN_KEY 8
#define FIRE_KEY 9

struct Input{
    unsigned int keyname;
    int keycode;
    int state;
    bool operator<(const Input& other) const { return keyname < other.keyname; }
};

class InputSystem
{
    std::vector<Input> inputs;

public:
    InputSystem();
    void Update(GLFWwindow* window);

    bool IsKeyPressed(unsigned int keyName);

    bool IsKeyReleased(unsigned int keyName);
};