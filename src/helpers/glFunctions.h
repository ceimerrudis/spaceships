#pragma once
#include "GlobalInclude.h"
#include <glad/glad.h>
#include "glfw3.h"

void InitGlad();

GLFWwindow* CreateWindow(std::string WindowName, int width = 640, int height = 640);