#pragma once
#include <glad/glad.h>
#include "glfw3.h"
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include <vector>
#include <memory>

class OpenGLResourceLibrary{
    std::vector<std::shared_ptr<unsigned int>> buffers;
    std::vector<std::shared_ptr<unsigned int>> textures;
    std::vector<std::shared_ptr<unsigned int>> vaObjects;
    std::vector<std::shared_ptr<unsigned int>> shaders;
public:
    std::shared_ptr<unsigned int> CreateBuffer();

    std::shared_ptr<unsigned int> CreateTexture();

    std::shared_ptr<unsigned int> CreateVertexArrayObject();

    std::shared_ptr<unsigned int> CreateShader();

    void Cleanup();

    ~OpenGLResourceLibrary();
};
