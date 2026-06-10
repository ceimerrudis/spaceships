#include "SpaceshipGame.h"
#include "cat/cat.h"
#include <memory.h>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using namespace cat;

void SpaceshipGame::InitCamera(shared_ptr<EntityHandle> cameraEntity)
{
	cameraEntity->Init(this);
	cameraEntity->entity.AddComponent<Transform>(this);  
	cameraEntity->entity.AddComponent<CameraData>(this);
	cameraEntity->entity.GetComponent<CameraData>(this).RecalculateProjectionMatrix(BaseScreenWidth, BaseScreenHeight, 400.0);
	renderer->SetUsedCamera(this, cameraEntity);
}

void SpaceshipGame::InitPlayer(shared_ptr<EntityHandle> playerEntity)
{
	gameData.viewpointType = ViewpointTypes::ThirdPerson;
	playerEntity->Init(this);
	Entity entity = playerEntity->entity;
	Transform& transform = entity.AddComponent<Transform>(this);
	transform.position = Vector<float, 3>{0,0,0};
	transform.UpdateTransformationMatrix();
	
	Renderable& renderable = entity.AddComponent<Renderable>(this, this, d3ObjectShaders);
	MeshData& meshData = entity.AddComponent<MeshData>(this, renderable, assetLoader->GetMeshAsset(spacehipAssetId));
	entity.AddComponent<Shading>(this, this, renderable, meshData);

	SpaceshipData& playerSpaceshipData = entity.AddComponent<SpaceshipData>(this);
	entity.AddComponent<Collider>(this, Vector<float, 3>{0.0f, 0.0f, 0.0f}, Vector<float, 3>{1.0f, 1.0f, 1.0f});

	playerSpaceshipData.isPlayer = true;
	playerSpaceshipData.isAlive = true;
}

void SpaceshipGame::InitEnemy(shared_ptr<EntityHandle> enemyEntity)
{
	enemyEntity->Init(this);
	Entity someone = enemyEntity->entity;
	
	Transform& someoneTransform = someone.AddComponent<Transform>(this);
	someoneTransform.position = Vector<float, 3>{5,0,1};
	someoneTransform.UpdateTransformationMatrix();
	
	Renderable& someone_renderable = someone.AddComponent<Renderable>(this, this, d3ObjectShaders);
	MeshData& someone_meshData = someone.AddComponent<MeshData>(this, someone_renderable, assetLoader->GetMeshAsset(cubeAssetId));
	someone.AddComponent<Shading>(this, this, someone_renderable, someone_meshData);
	someone.AddComponent<SpaceshipData>(this);
	someone.AddComponent<Collider>(this, Vector<float, 3>{0.0f, 0.0f, 0.0f}, Vector<float, 3>{1.0f, 1.0f, 1.0f});
}

void SpaceshipGame::InitSkybox(shared_ptr<EntityHandle> skyboxEntity)
{
	skyboxEntity->Init(this);
	skyboxEntity->entity.AddComponent<Transform>(this);
	skyboxEntity->entity.AddComponent<Renderable>(this, this, skyboxShaders);
	Renderable& cubemap_renderable = skyboxEntity->entity.GetComponent<Renderable>(this);
	skyboxEntity->entity.AddComponent<MeshData>(this, cubemap_renderable, assetLoader->GetMeshAsset(cubeMapAssetId));
	skyboxEntity->entity.AddComponent<ModelTexture>(this, textureManager->AddCubemapTexture(
	TextureType::CubeMap, 
	std::array<uint64_t, 6>
	{
		skyboxImageRight,
		skyboxImageLeft,
		skyboxImageBottom,
		skyboxImageTop,
		skyboxImageMiddle,
		skyboxImageFarRight,
	}));
}

void SpaceshipGame::InitCockpit(
shared_ptr<EntityHandle> cockpitEntity, 
shared_ptr<EntityHandle> throttleTextEntity,
shared_ptr<EntityHandle> posTextEntity,
shared_ptr<EntityHandle> instrumentEntity,
shared_ptr<EntityHandle> indicatorEntity)
{
	{
		cockpitEntity->Init(this);
		UITransform& uiTransform = cockpitEntity->entity.AddComponent<UITransform>(this);
		Renderable& renderable = cockpitEntity->entity.AddComponent<Renderable>(this, this, imageShaders);
		ImageData& imageData = cockpitEntity->entity.AddComponent<ImageData>(this, renderable);
		imageData.textureKey = textureManager->AddTexture(TextureType::Texture2D, cockpitImage);
		uiTransform.SetPositionAndSizeWithAnchors(this, renderable, Vector<float, 4>{0, 0, 0, 0}, Vector<float, 4>{1, 0, 1, 0});
	}
	
	{
		throttleTextEntity->Init(this);
		Renderable& renderable = throttleTextEntity->entity.AddComponent<Renderable>(this, this, textShaders);
		UITransform& uiTransform = throttleTextEntity->entity.AddComponent<UITransform>(this);
		throttleTextEntity->entity.AddComponent<ImageData>(this, renderable);
		TextData& textData = throttleTextEntity->entity.AddComponent<TextData>(this, renderable, motomangFontAssetId);
		uiTransform.SetPositionAndSizeWithAnchors(this, renderable, Vector<float, 4>{0.21, 0.0, 0.12, 0.0}, Vector<float, 4>{0.2, 0.0, 0.2, 0.0});
		//uiTransform.SetPositionAndSizeWithAnchors(this, renderable, Vector<float, 4>{0.5, 0.0, 0.5, 0.0}, Vector<float, 4>{0.5, 0.0, 0.5, 0.0});
		textData.SetDirection(Vector<float, 3>{0.6, 0.6, 0});
	}
	
	{
		posTextEntity->Init(this);
		Renderable& renderable = posTextEntity->entity.AddComponent<Renderable>(this, this, textShaders);
		UITransform& uiTransform = posTextEntity->entity.AddComponent<UITransform>(this);
		posTextEntity->entity.AddComponent<ImageData>(this, renderable);
		TextData& textData = posTextEntity->entity.AddComponent<TextData>(this, renderable, motomangFontAssetId);
		uiTransform.SetPositionAndSizeWithAnchors(this, renderable, Vector<float, 4>{0.2, 0, 0.03, 0}, Vector<float, 4>{0.6, 0, 0.16, 0});
		textData.SetDirection(Vector<float, 3>{1, 0, 0});
	}
	
	{
		instrumentEntity->Init(this);
		UITransform& uiTransform = instrumentEntity->entity.AddComponent<UITransform>(this);
		Renderable& renderable = instrumentEntity->entity.AddComponent<Renderable>(this, this, imageShaders);
		ImageData& imageData = instrumentEntity->entity.AddComponent<ImageData>(this, renderable);
		imageData.textureKey = textureManager->AddTexture(TextureType::Texture2D, instrumentImage);
		uiTransform.SetPositionAndSizeWithAnchors(this, renderable, Vector<float, 4>{0.5, -25, 0.3, -25}, Vector<float, 4>{0, 50, 0, 50});
	}
	
	{
		indicatorEntity->Init(this);
		UITransform& uiTransform = indicatorEntity->entity.AddComponent<UITransform>(this);
		Renderable& renderable = indicatorEntity->entity.AddComponent<Renderable>(this, this, imageShaders);
		ImageData& imageData = indicatorEntity->entity.AddComponent<ImageData>(this, renderable);
		imageData.textureKey = textureManager->AddTexture(TextureType::Texture2D, indicatorImage);
		uiTransform.SetPositionAndSizeWithAnchors(this, renderable, Vector<float, 4>{0, 10, 0, 10}, Vector<float, 4>{0, 10, 0, 10});
	}
}

void SpaceshipGame::InitAsteroid(shared_ptr<EntityHandle> asteroidEntity)
{
	asteroidEntity->Init(this);
	Transform& transform = asteroidEntity->entity.AddComponent<Transform>(this);
	Renderable& renderable = asteroidEntity->entity.AddComponent<Renderable>(this, this, d3ObjectShaders);
	AsteroidData& asteroidData = asteroidEntity->entity.AddComponent<AsteroidData>(this);
	//TODO fix asteroid generation and swap with model
	MeshData& meshData = asteroidEntity->entity.AddComponent<MeshData>(this, renderable, assetLoader->GetMeshAsset(asteroidAssetId));//asteroidData.mesh
	asteroidEntity->entity.AddComponent<Shading>(this, this, renderable, meshData);
	asteroidEntity->entity.AddComponent<Collider>(this, Vector<float, 3>{0.0f, 0.0f, 0.0f}, Vector<float, 3>{5.0f, 5.0f, 5.0f});
	
	transform.position = Vector<float, 3>{ Random::RandomF(-200, 200), Random::RandomF(-200, 200), Random::RandomF(-200, 200)};
	transform.scale = Vector<float, 3>{ Random::RandomF(10, 20), Random::RandomF(10, 20), Random::RandomF(10, 20)};
	//transform.position = Vector<float, 3>{ 0.0, 0.0, 10.0 };
	transform.UpdateTransformationMatrix();
}

void SpaceshipGame::InitGame()
{
	gameData.physicsSystem = std::make_shared<PhysicsSystem>();
	
	gameData.cameraUsed = std::make_shared<EntityHandle>();
	InitCamera(gameData.cameraUsed);

	gameData.spaceShips.push_back(std::make_shared<EntityHandle>());
	gameData.playerId = gameData.spaceShips.size() - 1;
	InitPlayer(gameData.spaceShips[gameData.playerId]);

	gameData.spaceShips.push_back(std::make_shared<EntityHandle>());
	InitEnemy(gameData.spaceShips[gameData.spaceShips.size() - 1]);

	gameData.cubemapEntity = std::make_shared<EntityHandle>();
	InitSkybox(gameData.cubemapEntity);

	gameData.cockpitEntity = std::make_shared<EntityHandle>();
	gameData.throttleTextEntity = std::make_shared<EntityHandle>();
	gameData.posTextEntity = std::make_shared<EntityHandle>();
	gameData.instrumentEntity = std::make_shared<EntityHandle>();
	gameData.indicatorEntity = std::make_shared<EntityHandle>();
	InitCockpit(gameData.cockpitEntity, gameData.throttleTextEntity, gameData.posTextEntity, gameData.instrumentEntity, gameData.indicatorEntity);

    for(int i = 0; i < 20; i++)
    {
        shared_ptr<EntityHandle> asteroid = gameData.asteroids.emplace_back(std::make_shared<EntityHandle>());
		InitAsteroid(asteroid);
    }
}
