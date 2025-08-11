#pragma once
#include "GlobalInclude.h"
#include "GLerrorHandling.h"
#include "OpenGLResourceLibrary.h"
#include <memory>
#include "Shader.h"

std::string GetShader(const std::string& fileName);

void CheckShaderCompileStatus(GLuint shader, const char* shaderName);

void CheckProgramLinkStatus(GLuint program);

std::shared_ptr<Shader> LoadShader(std::string vertexFileName, std::string FragmentFileName, OpenGLResourceLibrary& glResLib);
