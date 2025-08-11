#pragma once
#include "GlobalInclude.h"
#include <glad/glad.h>
#include "glfw3.h"
#include "Logger.h"
#include "D3Object.h"
#include "D2Object.h"
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
#include <array>
#include "Spaceship.h"
#include "Camera.h"
#include "ShaderManaging.h"
#include "WorldObject.h"
#include "advancedMath.h"
#include "AssetLoader.h"
#include "GLerrorHandling.h"
#include "glFunctions.h"
#include "InputSystem.h"
#include "GlyphCache.h"
#include "CubemapObject.h"
#include "Shader.h"
#include "ModelObject.h"
#include "TextObject.h"
#include "TextureManager.h"
#include "OpenGLResourceLibrary.h"

using std::unique_ptr;
using std::shared_ptr;

class Game{
private:
    unique_ptr<AssetLoader> assetLoader;
    unique_ptr<GlyphCache> glyphCache;
    unique_ptr<OpenGLResourceLibrary> glResLib;
    std::shared_ptr<TextureManager> textureManager;
    unique_ptr<InputSystem> inputSystem;

    std::shared_ptr<Shader> textShaders;
    std::shared_ptr<Shader> imageShaders;
    std::shared_ptr<Shader> d3ObjectShaders;
    std::shared_ptr<Shader> skyboxShaders;

    unique_ptr<Camera> cameraUsed;
    std::vector<std::unique_ptr<Spaceship>> spaceShips;
    std::vector<TextObject> texts;
    int playerId;

    GLFWwindow* window;
public:
    Game();
   
    ~Game();

    bool Update();
};