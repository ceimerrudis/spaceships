#include "OpenGLResourceLibrary.h"
#include "GLerrorHandling.h"

std::shared_ptr<unsigned int> OpenGLResourceLibrary::CreateBuffer()
{
    std::shared_ptr<unsigned int> ptr = std::make_shared<unsigned int>(0);
    GL(glGenBuffers(1, ptr.get())); 
    buffers.emplace_back(ptr);
    return ptr;
}

std::shared_ptr<unsigned int> OpenGLResourceLibrary::CreateTexture()
{
    std::shared_ptr<unsigned int> ptr = std::make_shared<unsigned int>(0);
    GL(glGenTextures(1, ptr.get()));
    textures.emplace_back(ptr);
    return ptr;
}

std::shared_ptr<unsigned int> OpenGLResourceLibrary::CreateVertexArrayObject()
{
    std::shared_ptr<unsigned int> ptr = std::make_shared<unsigned int>(0);
    GL(glGenVertexArrays(1, ptr.get())); 
    vaObjects.emplace_back(ptr);
    return ptr;
}

std::shared_ptr<unsigned int> OpenGLResourceLibrary::CreateShader()
{
    std::shared_ptr<unsigned int> ptr = std::make_shared<unsigned int>(0);
    GL(*ptr = glCreateProgram());
    shaders.emplace_back(ptr);
    return ptr;
}

void OpenGLResourceLibrary::Cleanup()
{
    int n = buffers.size();
    for (int i = 0; i < n; i++)
    {
        if(buffers[i].use_count() == 1)
        {
            GL(glDeleteBuffers(1, buffers[i].get()));
        }
        else
        {
            LOG("cant delete buffer");
        }
    }  
    n = textures.size();
    for (int i = 0; i < n; i++)
    {
        if(textures[i].use_count() == 1)
        {
            GL(glDeleteTextures(1, textures[i].get()));
        }
        else
        {
            LOG("cant delete texture");
        }
    }  
    n = shaders.size();
    for (int i = 0; i < n; i++)
    {
        if(shaders[i].use_count() == 1)
        {
            GL(glDeleteProgram(*shaders[i]));
        }
        else
        {
            LOG("cant delete shader");
        }
    }  
    n = vaObjects.size();
    for (int i = 0; i < n; i++)
    {
        if(vaObjects[i].use_count() == 1)
        {
            GL(glDeleteVertexArrays(1, vaObjects[i].get()));
        }
        else
        {
            LOG("cant delete vao");
        }
    }   
}

OpenGLResourceLibrary::~OpenGLResourceLibrary()
{
    Cleanup();
}