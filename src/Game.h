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
#include "Collider.h"
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
#include "PhysicsSystem.h"
#include "ModelObject.h"
#include "TextObject.h"
#include "TextureManager.h"
#include "DebugDraw.h"
#include "OpenGLResourceLibrary.h"
#include "Debugger.h"
#include "Asteroid.h"
#include "Renderer.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

class Game{
private:
    unique_ptr<OpenGLResourceLibrary> glResLib;
    unsigned int currentNextId;
    unique_ptr<Renderer> renderer;
    unique_ptr<AssetLoader> assetLoader;
    unique_ptr<GlyphCache> glyphCache;
    unique_ptr<InputSystem> inputSystem;
    shared_ptr<TextureManager> textureManager;
    shared_ptr<PhysicsSystem> physicsSystem;

    shared_ptr<Shader> textShaders;
    shared_ptr<Shader> imageShaders;
    shared_ptr<Shader> d3ObjectShaders;
    shared_ptr<Shader> skyboxShaders;

    unique_ptr<Camera> cameraUsed;
    std::vector<shared_ptr<Spaceship>> spaceShips;
    std::vector<shared_ptr<Asteroid>> asteroids;
    std::vector<TextObject> texts;
    int playerId;
    bool cursorCaptured;

    GLFWwindow* window;
public:
    Game();
   
    ~Game();

    bool Update();

    void ShootLaser(Ray fireRay);

    weak_ptr<Spaceship> GetSpaceShip(unsigned int id);

    void DebugDrawLine(Vector<float, 3> origin, Vector<float, 3> direction, Matrix<float, 4> translation, Vector<float, 3> color = Vector<float, 3>{1, 0, 0});

    void DebugDrawCollider(Collider col, Matrix<float, 4> translation, Vector<float, 3> color = Vector<float, 3>{1, 0, 0});

    void DebugDrawPoint(Vector<float, 3> pos, Matrix<float, 4> translation, Vector<float, 3> color = Vector<float, 3>{1, 0, 0});

    void KillSpaceship(unsigned int entityId);
};