#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Game.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

void MakeDebutgDataFromCiollider(Collider col, std::vector<float>* vert, std::vector<unsigned int>* ind);

Game::Game()
{
    currentNextId = 1;
    assetLoader = std::make_unique<AssetLoader>(); 
    glyphCache = std::make_unique<GlyphCache>(*assetLoader);
    //Move variables out
    int cockpitImage = assetLoader->LoadImage("cockpit.png");
    int instrumentImage = assetLoader->LoadImage("instrument.png");
    int indicatorImage = assetLoader->LoadImage("indicator.png");
    int skyboxImageRight    = assetLoader->LoadImage("skybox2_c00.bmp");//right +x
    int skyboxImageLeft     = assetLoader->LoadImage("skybox2_c01.bmp");//left -x
    int skyboxImageTop      = assetLoader->LoadImage("skybox2_c02.bmp");//top +y
    int skyboxImageBottom   = assetLoader->LoadImage("skybox2_c03.bmp");//bottom -y
    int skyboxImageFarRight = assetLoader->LoadImage("skybox2_c05.bmp");//far_right +z
    int skyboxImageMiddle   = assetLoader->LoadImage("skybox2_c04.bmp");//middle -z

    assetLoader->LoadObject("spaceship.obj");
    assetLoader->LoadObject("cube.obj");

    assetLoader->LoadFont("mechanical-font/Mechanical-g5Y5.otf");
    assetLoader->LoadFont("motomang-font/Motomangucode-p7Jj1.ttf");

    window = CreateWindow("spaceships");
    InitGlad();
    cursorCaptured = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glResLib = std::make_unique<OpenGLResourceLibrary>();;
    
    //text shaders
    textShaders = LoadShader("text_vertex.glsl", "text_fragment.glsl", *glResLib);
    textShaders->AddUniform(TEXT_TEXTURE_SLOT, "u_Texture", UniformType::Int);
    //text shaders end
    
    //image shaders
    imageShaders = LoadShader("image_vertex.glsl", "image_fragment.glsl", *glResLib);
    imageShaders->AddUniform(IMAGE_TEXTURE_SLOT, "u_Texture", UniformType::Int);
    //image shaders end

    //D3 object shaders
    d3ObjectShaders = LoadShader("d3_vertex.glsl", "d3_fragment.glsl", *glResLib);
    d3ObjectShaders->AddUniform(D3_WORLD_TRANSFORM, "u_worldPlaneTransf", UniformType::Mat4);
    d3ObjectShaders->AddUniform(D3_OBSERVER_PLANE, "u_observerPlane", UniformType::Mat4);
    d3ObjectShaders->AddUniform(D3_VIEW_POSITION, "u_viewPos", UniformType::Vec3);
    d3ObjectShaders->AddUniform(D3_LIGHT_DIRECTION, "u_lightDirection", UniformType::Vec3);
    d3ObjectShaders->AddUniform(D3_PROJECTION_MATRIX, "u_projMatrix", UniformType::Mat4);
    //D3 object shaders end

    //Skybox shaders
    skyboxShaders = LoadShader("skybox_vertex.glsl", "skybox_fragment.glsl", *glResLib);
    skyboxShaders->AddUniform(SKYBOX_VIEW_MATRIX, "u_view", UniformType::Mat4);
    skyboxShaders->AddUniform(SKYBOX_TEXTURE_SLOT, "u_skybox", UniformType::Int);
    skyboxShaders->AddUniform(SKYBOX_PROJECTION_MATRIX, "u_projection", UniformType::Mat4);
    //Skybox shaders end

    physicsSystem = std::make_shared<PhysicsSystem>();
    spaceShips.emplace_back(std::make_shared<Spaceship>(currentNextId++, assetLoader->meshes[0], d3ObjectShaders, *glResLib, *physicsSystem));

    playerId = spaceShips.size() - 1;
    spaceShips[playerId]->isPlayer = true;
    spaceShips[playerId]->position.data[0] = -10;
    
    cameraUsed = std::make_unique<Camera>(spaceShips[playerId].get());
    d3ObjectShaders->AssignDataToUniform(D3_PROJECTION_MATRIX,   (cameraUsed->projectionMatrix).data);
    skyboxShaders->AssignDataToUniform(SKYBOX_PROJECTION_MATRIX, (cameraUsed->projectionMatrix).data);

    spaceShips.emplace_back(std::make_shared<Spaceship>(currentNextId++, assetLoader->meshes[0], d3ObjectShaders, *glResLib, *physicsSystem));
    spaceShips.emplace_back(std::make_shared<Spaceship>(currentNextId++, assetLoader->meshes[0], d3ObjectShaders, *glResLib, *physicsSystem));
    spaceShips[2]->position = {10, 10, 4};

    textureManager = std::make_shared<TextureManager>(*assetLoader, *glResLib);
    renderer = std::make_unique<Renderer>(textureManager);
    renderer->SetLightDirection({0.468521, 0.624695, -0.624695});

    cameraUsed->skybox = std::make_unique<CubemapObject>(assetLoader->meshes[1], skyboxShaders, std::array<TaggedTextureResource*, 6>
        {
            &assetLoader->GetResource(skyboxImageRight),
            &assetLoader->GetResource(skyboxImageLeft),
            &assetLoader->GetResource(skyboxImageBottom),
            &assetLoader->GetResource(skyboxImageTop),
            &assetLoader->GetResource(skyboxImageMiddle),
            &assetLoader->GetResource(skyboxImageFarRight),
        }
        , textureManager, *glResLib);
    
    //texts.emplace_back(*glResLib, textShaders, "FPS:", 28, vector2{0, 0}, vector3{1, 0, 0}, textureManager, *glyphCache);

    cameraUsed->throttleText = std::make_unique<TextObject>(*glResLib, textShaders, 
         28, //size
         vector2{-0.60, -0.75}, //position
         vector3{0.6, 0.6, 0},//direction
           *glyphCache);
    cameraUsed->PosText = std::make_unique<TextObject>(*glResLib, textShaders, 
         28, //size
         vector2{-0.30, -0.8}, //position
         vector3{1, 0, 0},//direction
           *glyphCache);
    cameraUsed->cockpit = std::make_unique<D2Object>(imageShaders, vector2{-1, -1}, vector2{1, 1}, assetLoader->GetResource(cockpitImage), textureManager, *glResLib);
    cameraUsed->instrument = std::make_unique<D2Object>
    (imageShaders, vector2{-0.1, -0.6}, vector2{0.1, -0.4}, 
    assetLoader->GetResource(instrumentImage), textureManager, *glResLib);
    cameraUsed->indicator = std::make_unique<D2Object>
    (imageShaders, vector2{-0.02, -0.52}, vector2{0.02, -0.48}, 
    assetLoader->GetResource(indicatorImage), textureManager, *glResLib);
    
    for(int i = 0; i < 20; i++)
    {
        asteroids.emplace_back(std::make_shared<Asteroid>(currentNextId++, d3ObjectShaders, *glResLib, *physicsSystem));
    }
    //OpenGl uzstādījumi
    GL(glEnable(GL_BLEND));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL(glEnable(GL_DEPTH_TEST));//Ieslēdzam automātiski izveidoto dziļuma tekstūru
    GL(glDepthFunc(GL_LESS));//Dod priekšroku punktiem ar mazāku z vērtību
    GL(glEnable(GL_CULL_FACE));
    GL(glFrontFace(GL_CCW));
    GL(glPolygonMode(GL_FRONT, GL_FILL));//Aizpildām figūras GL_FILL GL_LINE
    GL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

    inputSystem = std::make_unique<InputSystem>(window);
}

bool Game::Update()
{
    inputSystem->Update(window);
    int liveEnemies = 0;
    int n = spaceShips.size();
    bool stopGame = false;
    for(int i = 0; i < n; i++)
    {
        if(spaceShips[i]->isAlive)
        {
            if(!spaceShips[i]->isPlayer)liveEnemies++;
        
            spaceShips[i]->update(*inputSystem, this);
        }
    }
    n = asteroids.size();
    for (int i = 0; i < n; i++)
    {
        asteroids[i]->update(this);   
    }
    
    physicsSystem->CheckCollisions(this);

    if(liveEnemies == 0)
    {
        spaceShips.emplace_back(std::make_shared<Spaceship>(currentNextId++, assetLoader->meshes[0], d3ObjectShaders, *glResLib, *physicsSystem));
    }

    physicsSystem->Cleanup();

    if(inputSystem->IsKeyUp(RELEASE_CURSOR))
    {
        if(cursorCaptured)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        cursorCaptured = !cursorCaptured;
    }

    if (glfwWindowShouldClose(window))
    {
        KillSpaceship(spaceShips[playerId]->id);
        return false;
    }
    glfwPollEvents();
    GL(glClear(GL_COLOR_BUFFER_BIT));
    GL(glClear(GL_DEPTH_BUFFER_BIT));
    if(DEBUG){
        //LOG("camMat", cam.WorldToObserverSpaceMatrix());
        //LOG("projMat", ProjectionMatrix);
    }
    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);
    
    //draw camera
    vector2i screenSize;
    glfwGetFramebufferSize(window, &screenSize.x(), &screenSize.y());
    renderer->SetScreenSize(screenSize);
    cameraUsed->Render(*renderer, textureManager);
    //draw spaceships
    vector3 l = {0.468521, 0.624695, -0.624695};
    DebugDrawPoint((l * 1000), Identity(), {1,1,0});
    //draw texts
    n = texts.size();
    for (int i = 0; i < n; i++)
    {
        renderer->Render(&texts[i]);
    }
    //DebugDrawCollider(physicsSystem->GetFirstColliderBelongingTo(spaceShips[1]->id), spaceShips[1]->translationMat, {1,0,1});
    //DebugDrawLine({0,0,0}, spaceShips[playerId]->forward,  Identity(), {1,0,1});
    //DebugDrawLine({0,0,0}, {1,0,0},  Identity(), {1,0,0});
    //DebugDrawLine({0,0,0}, {0,1,0},  Identity(), {0,1,0});
    //DebugDrawLine({0,0,0}, {0,0,1},  Identity(), {0,0,1});

    d3ObjectShaders->AssignDataToUniform(D3_OBSERVER_PLANE, cameraUsed->WorldToObserverSpaceMatrix().data);
    d3ObjectShaders->AssignDataToUniform(D3_VIEW_POSITION, &cameraUsed->position.data[0]);
    n = spaceShips.size();
    for(int i = 0; i < n; i++)
    {
        if(DEBUG){
            //LOG((string)"spaceShip "+(char)('0' + i), spaceShips[i].translationMat);
        }
        if(!spaceShips[i]->isPlayer && spaceShips[i]->isAlive)
        {            
            renderer->Render(spaceShips[i].get());
        }
    }
    n = asteroids.size();
    for(int i = 0; i < n; i++)
    {     
        renderer->Render(asteroids[i].get());
    }

    GL(glfwSwapBuffers(window));
    return true;
}

Game::~Game()
{
    for(int i = 0; i < spaceShips.size(); i++)
    {
        if(spaceShips[i]->isAlive)
        {
            KillSpaceship(spaceShips[i]->id);
        }
    }
}

void Game::ShootLaser(Ray fireRay)
{
    physicsSystem->ShootLaser(fireRay, this);
}

weak_ptr<Spaceship> Game::GetSpaceShip(unsigned int id)
{
    int n = spaceShips.size();
    for (int i = 0; i < n; i++)
    {
        if(spaceShips[i]->id == id)
        {
            return spaceShips[i];
        }
    }
    error("Did not find ship");
}

void Game::DebugDrawLine(vector3 origin, vector3 direction, matrix4 translation, vector3 color)
{
    std::vector<float> v;
    v = {origin.x(), origin.y(), origin.z(),
        origin.x()+direction.x()*2, origin.y()+direction.y()*2, origin.z()+direction.z()*2};
    DebugDraw g(v, cameraUsed->projectionMatrix, color);
    g.Render(translation, cameraUsed->WorldToObserverSpaceMatrix());
}

void Game::DebugDrawCollider(Collider col, matrix4 translation, vector3 color)
{
    std::vector<float> v;
    std::vector<unsigned int> i;
    
    vector3 halfSize;
    halfSize.data[0] = col.width  * 0.5f;
    halfSize.data[1] = col.height * 0.5f;
    halfSize.data[2] = col.length * 0.5f;
    vector3 min = (vector3){0,0,0} - halfSize;
    vector3 max = (vector3){0,0,0} + halfSize;

    // Define 8 corners of the box
    v = {
        min.x(), min.y(), min.z(), // 0
        max.x(), min.y(), min.z(), // 1
        max.x(), max.y(), min.z(), // 2
        min.x(), max.y(), min.z(), // 3
        min.x(), min.y(), max.z(), // 4
        max.x(), min.y(), max.z(), // 5
        max.x(), max.y(), max.z(), // 6
        min.x(), max.y(), max.z()  // 7
    };
   i = {
        // Front face
        0, 2, 1, 2, 0, 3,
        // Back face
        5, 7, 4, 7, 5, 6,
        // Left face
        4, 3, 0, 3, 4, 7,
        // Right face
        1, 6, 5, 6, 1, 2,
        // Top face
        3, 6, 2, 6, 3, 7,
        // Bottom face
        4, 1, 5, 1, 4, 0
    };

    DebugDraw g(v, i, cameraUsed->projectionMatrix, color);
    g.Render(translation, cameraUsed->WorldToObserverSpaceMatrix());
}

void Game::DebugDrawPoint(vector3 pos, matrix4 translation, vector3 color)
{
    std::vector<float> v;
    std::vector<unsigned int> i;
    
    //translation(0, 3) +=;
    //translation(1, 3) +=;
    //translation(2, 3) +=;

    vector3 halfSize;
    halfSize.data[0] = 0.3f * 100;
    halfSize.data[1] = 0.3f * 100;
    halfSize.data[2] = 0.3f * 100;
    vector3 min = (vector3){0,0,0} - halfSize;
    vector3 max = (vector3){0,0,0} + halfSize;
    min = min + pos;
    max = max + pos;
    // Define 8 corners of the box
    v = {
        min.x(), min.y(), min.z(), // 0
        max.x(), min.y(), min.z(), // 1
        max.x(), max.y(), min.z(), // 2
        min.x(), max.y(), min.z(), // 3
        min.x(), min.y(), max.z(), // 4
        max.x(), min.y(), max.z(), // 5
        max.x(), max.y(), max.z(), // 6
        min.x(), max.y(), max.z()  // 7
    };
   i = {
        // Front face
        0, 2, 1, 2, 0, 3,
        // Back face
        5, 7, 4, 7, 5, 6,
        // Left face
        4, 3, 0, 3, 4, 7,
        // Right face
        1, 6, 5, 6, 1, 2,
        // Top face
        3, 6, 2, 6, 3, 7,
        // Bottom face
        4, 1, 5, 1, 4, 0
    };

    DebugDraw g(v, i, cameraUsed->projectionMatrix, color);
    g.Render(translation, cameraUsed->WorldToObserverSpaceMatrix());
}

void Game::KillSpaceship(unsigned int entityId)
{
    weak_ptr<Spaceship> shipToKill = GetSpaceShip(entityId);
    
    if(!shipToKill.lock()->isAlive)
    {
        return;
    }
    
    if(shipToKill.lock()->isPlayer)
    {
        LOG("Player dead!");
        glfwSetWindowShouldClose(window, true);
    }
    physicsSystem->MarkColliderForDeletion(entityId);
    shipToKill.lock()->isAlive = false;
    #if DEBUG_MEMORY
        LOG("deleted memory ", normalIndexes);
    #endif
    delete[] shipToKill.lock()->normalIndexes;
}
