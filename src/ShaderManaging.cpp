#include "ShaderManaging.h"
#include "GLerrorHandling.h"
#include "Logger.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using std::string;

string GetShader(const string& fileName)
{
    std::filesystem::path fullPath = std::filesystem::path("res/shaders/") / fileName;
    std::ifstream shaderFile(fullPath);

    if (!shaderFile.is_open()) {
        error("Failed to open shader file: " + fullPath.string());
    }

    string output;
    for (string line; std::getline(shaderFile, line); ) 
    {
        output+=line+"\n";
    }
    
    shaderFile.close();
    return output;
}

void CheckShaderCompileStatus(GLuint shader, const char* shaderName) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        string log(logLength, ' ');
        glGetShaderInfoLog(shader, logLength, nullptr, &log[0]);
        string shName = shaderName;
        error("compiling shader (" + shName + "):\n" + log);
    }
}

void CheckProgramLinkStatus(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        string log(logLength, ' ');
        glGetProgramInfoLog(program, logLength, nullptr, &log[0]);
        error("linking program:\n" + log);
    }
}

std::shared_ptr<Shader> LoadShader(string vertexFileName, string FragmentFileName, OpenGLResourceLibrary& glResLib)
{
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexFileName+FragmentFileName);
    shader->shaderKey = glResLib.CreateShader();
    string a = GetShader(vertexFileName);
    const char*  vertexShader = a.c_str();
    GL(unsigned int vs = glCreateShader(GL_VERTEX_SHADER));
    GL(glShaderSource(vs, 1, &vertexShader, NULL));
    GL(glCompileShader(vs));
    CheckShaderCompileStatus(vs, vertexFileName.c_str());
    a = GetShader(FragmentFileName);
    const char*  fragmentShader = a.c_str();
    GL(unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER));
    GL(glShaderSource(fs, 1, &fragmentShader, NULL));
    GL(glCompileShader(fs));
    CheckShaderCompileStatus(fs, FragmentFileName.c_str());
    GL(glAttachShader(*shader->shaderKey, vs));
    GL(glAttachShader(*shader->shaderKey, fs));
    GL(glLinkProgram(*shader->shaderKey));
    CheckProgramLinkStatus(*shader->shaderKey);
    GL(glValidateProgram(*shader->shaderKey));

    GL(glDeleteShader(vs));
    GL(glDeleteShader(fs));
    GL(glUseProgram(*shader->shaderKey));

    return shader;
}