#pragma once
#include "GlobalInclude.h"
#include "TextureResource.h"
#include "AssetLoader.h"
#include "TaggedTextureResource.h"
#include <vector>
#include <array>
#include <unordered_set>
#include "OpenGLResourceLibrary.h"

struct Texture{
    uint64_t resourceID;
    
    std::shared_ptr<unsigned int> textureKey;//texture key 
    unsigned int textureType;//texture type
    int textureUnit;//texture unit
    unsigned char* textureData;//texture data
    unsigned char** textures;//texture data

    int width;
    int height;
    unsigned int dataFormat;
    
    inline bool operator==(const Texture& other) const {
        return this->textureKey == other.textureKey;
    }
};

struct TextureManager{
private:
    std::string myTag = "TextureManager";

    void ReleaseCubemapTexture(Texture& texture);

    void ReleaseFlatTexture(Texture& texture);

    Texture CreateTexture(unsigned int textureType, TextureResource& textureResource, bool* found, bool genTexture = true);
public:
    int slotCount;

    std::vector<Texture> textures;
    std::unordered_set<unsigned int> loadedTextures;
    AssetLoader& assetLoader;
    OpenGLResourceLibrary& glResLib;

    std::shared_ptr<unsigned int> AddTexture(unsigned int textureType, TaggedTextureResource& textureResource);

    std::shared_ptr<unsigned int> AddTexture(unsigned int textureType, TextureResource& textureResource);

    std::shared_ptr<unsigned int> AddCubemapTexture(unsigned int textureType, std::array<TaggedTextureResource*, 6> textureResources);

    int GetAvailableTextureUnit(unsigned int textureType);

    void ReleaseTexture(std::shared_ptr<unsigned int> textureKey);

    int LoadTexture(std::shared_ptr<unsigned int> textureKey);

    Texture& GetTexture(std::shared_ptr<unsigned int> textureKey);

    inline bool IsTextureLoaded(unsigned int textureKey)
    {
        return loadedTextures.find(textureKey) != loadedTextures.end();
    }

    TextureManager(AssetLoader& assetLoader, OpenGLResourceLibrary& glResLib);

    ~TextureManager();
};
