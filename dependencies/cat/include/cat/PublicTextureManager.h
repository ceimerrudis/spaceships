#pragma once
#include <memory>
#include <array>
#include <filesystem>
#include <cat/PublicAssetLoader.h>
#include "cat/TextureType.h"

namespace cat
{
class TextureManager;
class TaggedTextureResource;
class OpenGLResourceLibrary;
class TextureResource;
class Mesh;
class PublicTextureManager
{
public:
	std::shared_ptr<TextureManager> textureManager;
	
	PublicTextureManager(std::shared_ptr<PublicAssetLoader> assetLoader, std::shared_ptr<OpenGLResourceLibrary> glResLib);
	
	std::shared_ptr<unsigned int> AddTexture(TextureType textureType, uint64_t textureId, TextureResource textureResource);
	
	std::shared_ptr<unsigned int> AddTexture(TextureType textureType, uint64_t textureId);

    std::shared_ptr<unsigned int> AddCubemapTexture(TextureType textureType, std::array<uint64_t, 6> textureIds);
};
}