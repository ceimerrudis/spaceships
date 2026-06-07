#pragma once
#include <memory>
#include <filesystem>
#include "cat/Vector.h"
#include "cat/Renderable.h"
#include "cat/ModelTexture.h"
#include "cat/ImageData.h"
#include "cat/TextData.h"
#include "cat/Shading.h"
#include "cat/Transform.h"
#include "cat/UITransform.h"
#include "cat/Entity.h"
#include "cat/PublicTextureManager.h"
#include "cat/EntityHandle.h"

namespace cat
{
class Renderer;
class Game;
class TaggedTextureResource;
class TextureManager;
class Mesh;
class PublicRenderer
{
public:
	PublicRenderer(Game* game, std::shared_ptr<PublicTextureManager> textureManager);
	
	std::unique_ptr<Renderer> renderer;
	
	bool CheckRenderability(std::shared_ptr<EntityHandle> entity);
	
	void Render(std::shared_ptr<EntityHandle> entity);
	
	void Render(Transform & transform, Renderable& renderrable, Shading& shading);

	void Render(Transform & transform, Renderable& renderrable, ModelTexture& modelTexture);

	void Render(UITransform & transform, Renderable& renderrable, TextData& textData, ImageData& imageData);

	void Render(UITransform & transform, Renderable& renderrable, ImageData& imageData);
	
	void SetLightDirection(Vector<float, 3> direction);
	
	void SetUsedCamera(Game* game, std::shared_ptr<EntityHandle> camera_entity);
};
}