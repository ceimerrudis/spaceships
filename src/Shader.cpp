#include "Shader.h"
#include "GlErrorHandling.h"

void Shader::AddUniform(std::string commonName, std::string realName, UniformType dataType)
{
    if(uniforms.find(commonName) != uniforms.end())
    {
        error("common names match");
    }
    Uniform unif;
    GL(unif.location = glGetUniformLocation(*shaderKey, realName.c_str()));
    unif.name = realName;
    unif.type = dataType;
    uniforms.emplace(commonName, unif);
}

Shader::Shader(std::string name)
{
    this->name = name;
}

void Shader::AssignDataToUniform(std::string commonName, void* data)
{
    if(uniforms.find(commonName) == uniforms.end())
    {
        error("uniform not found. name: " + commonName + " shader: " + name);
    }
    Uniform& uniform = (*uniforms.find(commonName)).second;
    #if DEBUG_SHADERS
        LOG(uniform.type);
        LOG(uniform.location);
        LOG(uniform.name);
        LOG(commonName);
    #endif
    switch (uniform.type)
    {
    case UniformType::Float:
        glUniform1f(uniform.location, *(float*)data);
        break;
    case UniformType::Int:
        glUniform1i(uniform.location, *(int*)data);
        break;
    case UniformType::Vec4:
        glUniform4f(uniform.location, ((float*)data)[0], ((float*)data)[1], ((float*)data)[2], ((float*)data)[3]);
        break;
    case UniformType::Vec3:
        glUniform3f(uniform.location, ((float*)data)[0], ((float*)data)[1], ((float*)data)[2]);
        break;
    case UniformType::Mat4:
        glUniformMatrix4fv(uniform.location, 1, GL_TRUE, (float*)data);
        break;
    default:
        LOG(uniform.type);
        error("Unimplemented uniform assign operation");
        break;
    }
    GL();//catch any occured errors
}