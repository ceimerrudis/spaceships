#include <glad/glad.h>
#include "glfw3.h"
#include <iostream>
#include "GLErrorHandling.h"

bool GLLogCall(const char* fileName, int line) {
    bool notok = false;
    GLenum error;
    while (error = glGetError()) {
        std::cout << fileName << ":" <<line << " - line | OpenGL error - " << error << "\n";
        notok = true;
    }
    return notok;
}
