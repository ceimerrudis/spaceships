#pragma once
#include "GlobalInclude.h"
#include <glad/glad.h>
#include "glfw3.h"
#include <iostream>
#include "OpenGLResourceLibrary.h"
bool GLLogCall(const char* fileName, int line);
inline void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

//OpenGL kļūdu novērošana ir čakarīga tapēc izveidots Macros kas "ietin" komandu kļūdu pārbaudes kodā
#define GL(x) GLClearError();x;if (GLLogCall(__FILE__, __LINE__)) abort();

