#pragma once
#include "cat/Logger.h"
#include "cat/Vector.h"
#include "cat/Matrix.h"
#include "cat/AdvancedMath.h"

#include "cat/Shader.h"
#include "cat/Mesh.h"

#include "cat/Screen.h"
#include "cat/dependencies/entt/entt.hpp"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

namespace cat
{

class EntityHandle;
class TextData;
	
enum GameType {
  Game3D,
  Game2D,
  Other
}; 

class Window;
class Entity;
class OpenGLResourceLibrary;
class GlyphCache;
class InputSystem;
class TextureResource;
class TaggedTextureResource;
class PublicAssetLoader;
class PublicTextureManager;
class PublicRenderer;
class UITransform;

class Game
{
public:
    shared_ptr<OpenGLResourceLibrary> glResLib;
    unique_ptr<PublicRenderer> renderer;
    shared_ptr<PublicAssetLoader> assetLoader;
	
	shared_ptr<GlyphCache> glyphCache;
    shared_ptr<PublicTextureManager> textureManager;
    
protected:
	unique_ptr<InputSystem> inputSystem;
	
    shared_ptr<Shader> textShaders;
    shared_ptr<Shader> imageShaders;
    shared_ptr<Shader> d3ObjectShaders;
    shared_ptr<Shader> skyboxShaders;
	shared_ptr<Shader> tileShaders;

    std::string windowName;
    GameType type;


    bool cursorCaptured;
    int windowWidth;
    int windowHeight;

    unique_ptr<Window> window; 
public:
	Screen screen;
	unique_ptr<entt::registry> entt_registry;
	uint32_t currentNextId = 0;
	int quitingGame = false;

    Game(std::string windowName, int width, int height, GameType type, bool captureCursor);
   
    virtual ~Game();

    virtual bool Update();
	
	bool EndUpdate();

	void DestroyEntity(Entity& entity);
	
	void DestroyEntity(shared_ptr<EntityHandle> entity);

    void ToggleCursor();

	void RepositionUI();
	
	virtual void OnScreenResize(Vector<int, 2> newScreenSize, int WorldPixelScale = -1, int UIPixelScale = -1);
	
	template<typename T>
	std::span<T> GetAllComponents()
	{
		entt::storage_for<T>& storage = entt_registry->storage<T>();
		if (!storage || storage.size() == 0) return {};
		return std::span<T>(storage.raw()[0], storage.size());
	}
	
	template<typename T>
	std::span<const Entity> GetAllEntitiesWithComponent()
	{
		entt::storage_for_t<T>& storage = entt_registry->storage<T>();
		if (!storage || storage.size() == 0) return {};

		return std::span<const Entity>(reinterpret_cast<const Entity*>(storage.data()),storage.size());
	}
	
	void SetText(TextData& textData, std::string newText, int size);
};

bool MouseColisionOnUI(Vector<float, 2> mousePos, UITransform& transform, Screen& screen); 
}
