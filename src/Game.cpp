#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Game.h"

Game::Game()
{
    assetLoader = std::make_unique<AssetLoader>(); 
    glyphCache = std::make_unique<GlyphCache>(*assetLoader);
    //Move variables out
    int cockpitImage = assetLoader->LoadImage("cockpit.png");
    int skyboxImageTop = assetLoader->LoadImage("skybox_top.png");
    int skyboxImageLeft = assetLoader->LoadImage("skybox_left.png");
    int skyboxImageMiddle = assetLoader->LoadImage("skybox_middle.png");
    int skyboxImageRight = assetLoader->LoadImage("skybox_right.png");
    int skyboxImageFarRight = assetLoader->LoadImage("skybox_far_right.png");
    int skyboxImageBottom = assetLoader->LoadImage("skybox_bottom.png");

    assetLoader->LoadObject("spaceship.obj");
    assetLoader->LoadObject("cube.obj");

    assetLoader->LoadFont("mechanical-font/Mechanical-g5Y5.otf");
    assetLoader->LoadFont("motomang-font/Motomangucode-p7Jj1.ttf");

    window = CreateWindow("spaceships");
    InitGlad();
    
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
    d3ObjectShaders = LoadShader("vertex.glsl", "fragment.glsl", *glResLib);
    d3ObjectShaders->AddUniform(D3_WORLD_TRANSFORM, "u_worldPlaneTransf", UniformType::Mat4);
    d3ObjectShaders->AddUniform(D3_OBSERVER_PLANE, "u_observerPlane", UniformType::Mat4);
    d3ObjectShaders->AddUniform(D3_VIEW_POSITION, "u_viewPos", UniformType::Vec3);
    d3ObjectShaders->AddUniform(D3_LIGHT_DIRECTION, "u_lightDirection", UniformType::Vec3);
    d3ObjectShaders->AddUniform(D3_PROJECTION_MATRIX, "u_projMatrix", UniformType::Mat4);

    float lightDirection[3] = {0.468521, 0.624695, -0.624695};
    d3ObjectShaders->AssignDataToUniform(D3_LIGHT_DIRECTION, lightDirection);
    //D3 object shaders end

    //Skybox shaders
    skyboxShaders = LoadShader("skybox_vertex.glsl", "skybox_fragment.glsl", *glResLib);
    skyboxShaders->AddUniform(SKYBOX_VIEW_MATRIX, "u_view", UniformType::Mat4);
    skyboxShaders->AddUniform(SKYBOX_TEXTURE_SLOT, "u_skybox", UniformType::Int);
    skyboxShaders->AddUniform(SKYBOX_PROJECTION_MATRIX, "u_projection", UniformType::Mat4);

    
    //Skybox shaders end
    spaceShips.emplace_back(std::make_unique<Spaceship>(assetLoader->meshes[0], d3ObjectShaders, *glResLib));

    playerId = spaceShips.size() - 1;
    spaceShips[playerId]->isPlayer = true;
    spaceShips[playerId]->position.data[0] = -10;
    
    cameraUsed = std::make_unique<Camera>(spaceShips[playerId].get());
    d3ObjectShaders->AssignDataToUniform(D3_PROJECTION_MATRIX,   (cameraUsed->projectionMatrix).data);
    skyboxShaders->AssignDataToUniform(SKYBOX_PROJECTION_MATRIX, (cameraUsed->projectionMatrix).data);

    spaceShips.emplace_back(std::make_unique<Spaceship>(assetLoader->meshes[0], d3ObjectShaders, *glResLib));
    spaceShips.emplace_back(std::make_unique<Spaceship>(assetLoader->meshes[0], d3ObjectShaders, *glResLib));
    
    textureManager = std::make_unique<TextureManager>(*assetLoader, *glResLib);

    CubemapObject* skybox = new CubemapObject(assetLoader->meshes[1], skyboxShaders, std::array<TaggedTextureResource*, 6>
        {
            &assetLoader->GetResource(skyboxImageRight),
            &assetLoader->GetResource(skyboxImageLeft),
            &assetLoader->GetResource(skyboxImageBottom),
            &assetLoader->GetResource(skyboxImageTop),
            &assetLoader->GetResource(skyboxImageMiddle),
            &assetLoader->GetResource(skyboxImageFarRight),
        }
        , textureManager, *glResLib);
    TextObject* throttleText = new TextObject(*glResLib, textShaders, "THRTL:",
         28, //size
         vector2{-0.60, -0.75}, //position
         vector3{0.6, 0.6, 0},//direction
          textureManager, *glyphCache);
    D2Object* cockpit = new D2Object(imageShaders, vector2{-1, -1}, vector2{1, 1}, assetLoader->GetResource(cockpitImage),
     textureManager, *glResLib);

    cameraUsed->children.push_back(throttleText);
    cameraUsed->throttleText = cameraUsed->children.size() - 1;
    cameraUsed->children.push_back(cockpit);
    cameraUsed->cockpit = cameraUsed->children.size() - 1;
    cameraUsed->children.push_back(skybox);
    cameraUsed->skybox = cameraUsed->children.size() - 1;
    
    //OpenGl uzstādījumi
    GL(glEnable(GL_BLEND));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL(glEnable(GL_DEPTH_TEST));//Ieslēdzam automātiski izveidoto dziļuma tekstūru
    GL(glDepthFunc(GL_LESS));//Dod priekšroku punktiem ar mazāku z vērtību
    GL(glEnable(GL_CULL_FACE));
    GL(glFrontFace(GL_CCW));
    GL(glPolygonMode(GL_FRONT, GL_FILL));//Aizpildām figūras
    GL(glClearColor(1.0f, 0.0f, 1.0f, 1.0f));

    inputSystem = std::make_unique<InputSystem>();
}

bool Game::Update()
{
    if (glfwWindowShouldClose(window))
    {
        LOG("closing");
        return false;
    }
    inputSystem->Update(window);
    int liveEnemies = 0;
    for(int i = 0; i < spaceShips.size(); i++)
    {
        if(spaceShips[i]->isAlive)
        {
            if(!spaceShips[i]->isPlayer)liveEnemies++;
        
            spaceShips[i]->update(*inputSystem);
        }
        if(!spaceShips[playerId]->isAlive)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }

    if(liveEnemies == 0)
    {
        spaceShips.emplace_back(std::make_unique<Spaceship>(assetLoader->meshes[0], d3ObjectShaders, *glResLib));
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
    //draw texts
    int n = texts.size();
    for (int i = 0; i < n; i++)
    {
        texts[i].Render();
    }
    //draw camera
    vector2i screenSize;
    glfwGetFramebufferSize(window, &screenSize.x(), &screenSize.y());
    cameraUsed->Render(screenSize);
    //draw spaceships
    
    d3ObjectShaders->AssignDataToUniform(D3_OBSERVER_PLANE, cameraUsed->WorldToObserverSpaceMatrix().data);
    d3ObjectShaders->AssignDataToUniform(D3_VIEW_POSITION, &cameraUsed->position.data[0]);
    n = spaceShips.size();
    for(int i = 0; i < n; i++)
    {
        if(DEBUG){
            //LOG((string)"spaceShip "+(char)('0' + i), spaceShips[i].translationMat);
        }
        spaceShips[i]->Render();
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
            spaceShips[i]->die();
        }
    }
}