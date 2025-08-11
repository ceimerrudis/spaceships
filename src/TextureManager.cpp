#include "TextureManager.h"
#include "glad/glad.h"
#include "GLerrorHandling.h"
#include "OpenGLResourceLibrary.h"
#include "AssetLoader.h"
#include <vector>
#include <array>
#include <algorithm>
#include <memory>

TextureManager::TextureManager(AssetLoader& assetLoader, OpenGLResourceLibrary& glResLib)
:   assetLoader(assetLoader),
    glResLib(glResLib)
{
    GL(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &slotCount));
    GL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
}

int TextureManager::GetAvailableTextureUnit(unsigned int textureType)
{
    std::vector<bool> possibleSlots(slotCount);
    for(int i = 0; i < slotCount; i++)
    {
        possibleSlots[i] = true;
    }
    for(const Texture& textureResource : textures)
    {
        if(textureResource.textureType == textureType && textureResource.textureUnit != -1)
        {
            possibleSlots[textureResource.textureUnit] = false;
        }
    }

    for(int i = 0; i < slotCount; i++)
    {
        if(possibleSlots[i])
        {
            return i;
        }
    }

    for(Texture& textureResource : textures)
    {
        if(textureResource.textureUnit == 0 && textureResource.textureType == textureType)
        {
            loadedTextures.erase(*textureResource.textureKey);
            textureResource.textureUnit = -1;
        }
    }    
    return 0;
}

int TextureManager::LoadTexture(std::shared_ptr<unsigned int> textureKey)
{
    Texture& thisTexture = GetTexture(textureKey);
 
    if(IsTextureLoaded(*textureKey))
    {
        return thisTexture.textureUnit;
    }
    int textureUnit = GetAvailableTextureUnit(thisTexture.textureType);

    GL(glActiveTexture(GL_TEXTURE0+textureUnit));
    GL(glBindTexture(thisTexture.textureType, *textureKey));
    if(thisTexture.textureType == GL_TEXTURE_CUBE_MAP){
        for(int i = 0; i < 6; i++)
        {
            GL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, thisTexture.width, thisTexture.height, 0, thisTexture.dataFormat, GL_UNSIGNED_BYTE, thisTexture.textures[i]));
        }
    }
    else
    {
        GL(glTexImage2D(thisTexture.textureType, 0, GL_RGBA8, thisTexture.width, thisTexture.height, 0, thisTexture.dataFormat, GL_UNSIGNED_BYTE, thisTexture.textureData));
    }   

    GL(glTexParameteri(thisTexture.textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST));//GL_LINEAR
    GL(glTexParameteri(thisTexture.textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST));//GL_LINEAR
    GL(glTexParameteri(thisTexture.textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL(glTexParameteri(thisTexture.textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL(glTexParameteri(thisTexture.textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    thisTexture.textureUnit = textureUnit;
    loadedTextures.insert(*thisTexture.textureKey);

    return textureUnit;
}

Texture& TextureManager::GetTexture(std::shared_ptr<unsigned int> textureKey)
{
    for (Texture& textureResource : textures)
    {
        if(textureResource.textureKey == textureKey)
        {
            return textureResource;
        }
    }
    error("No textureResource found! Key: " + std::to_string(*textureKey));
}

std::shared_ptr<unsigned int> TextureManager::AddCubemapTexture(unsigned int textureType, std::array<TaggedTextureResource*, 6> textureResources)
{
    (*textureResources[0]).addTag(myTag);
    Texture cubeMapTexture = CreateTexture(textureType, *textureResources[0], true);
    cubeMapTexture.textureData = nullptr;
    
    cubeMapTexture.textures = new unsigned char*[6];
    #if DEBUG_MEMORY
        LOG("created memory ", cubeMapTexture.textures);
    #endif
    cubeMapTexture.textures[0] = (*textureResources[0]).data;
    for(int i = 1; i < 6; i++)
    {
        cubeMapTexture.textures[i] = (*textureResources[i]).data;
        //Checks nullptrs and adds tags to resources
        (*textureResources[i]).addTag(myTag);
        Texture tempTexture = CreateTexture(textureType, *textureResources[i], false);
    }

    textures.push_back(cubeMapTexture);
    return cubeMapTexture.textureKey;
}

std::shared_ptr<unsigned int> TextureManager::AddTexture(unsigned int textureType, TaggedTextureResource& textureResource)
{
    Texture tempTexture = CreateTexture(textureType, textureResource);
    textureResource.addTag(myTag);
    textures.push_back(tempTexture);

    return tempTexture.textureKey;
}

std::shared_ptr<unsigned int> TextureManager::AddTexture(unsigned int textureType, TextureResource& textureResource)
{
    Texture tempTexture = CreateTexture(textureType, textureResource);
    textures.push_back(tempTexture);

    return tempTexture.textureKey;
}

Texture TextureManager::CreateTexture(unsigned int textureType, TextureResource& textureResource, bool genTexture)
{
    int n = textures.size();
    for(int i = 0; i < n; i++)
    {
        if(textures[i].resourceID == textureResource.resourceID)
        {
            return textures[i];
        }
    }
    if(textureResource.data == nullptr)
    {
        error("nullPtr passed");
    }
    std::shared_ptr<unsigned int> textureKey;
    if(genTexture)
    {   
        textureKey = glResLib.CreateTexture();
    }
    
    
    unsigned int givenImageType;
    if(textureResource.channels == 1){
        givenImageType = GL_RED;
    }
    else if(textureResource.channels == 4){
        givenImageType = GL_RGBA;
    }
    else if (textureResource.channels == 3){
        givenImageType = GL_RGB;
    }
    else{
        LOG("Channel count ", textureResource.channels);
        error("This case (channels < 3 || > 4) is not yet implemented");
    }
    Texture tempTexture;
    tempTexture.textureKey = textureKey;
    tempTexture.textureType = textureType;
    tempTexture.textureUnit = -1;
    tempTexture.textureData = textureResource.data;

    tempTexture.width = textureResource.width;
    tempTexture.height = textureResource.height;
    tempTexture.dataFormat = givenImageType;

    return tempTexture;
}

void TextureManager::ReleaseTexture(std::shared_ptr<unsigned int> textureKey)
{
    Texture& textureToRelease = GetTexture(textureKey);
    if(textureToRelease.textureType == GL_TEXTURE_CUBE_MAP)
    {
        ReleaseCubemapTexture(textureToRelease);
    }
    else
    {
        ReleaseFlatTexture(textureToRelease);
    }
}

void TextureManager::ReleaseCubemapTexture(Texture& texture)
{
    for(TaggedTextureResource& textureResource: assetLoader.images)
    {
        for (int i = 0; i < 6; i++)
        {
            if(texture.textures[i] == textureResource.data)
            {
                textureResource.removeTag(myTag);
            }
        }
    }
    delete[] texture.textures;
    #if DEBUG_MEMORY
        LOG("deleting memory ", texture.textures);
    #endif
    textures.erase(std::remove(textures.begin(), textures.end(), texture), textures.end());
}

void TextureManager::ReleaseFlatTexture(Texture& texture)
{
    for(TaggedTextureResource& textureResource: assetLoader.images)
    {
        if(texture.textureData == textureResource.data)
        {
            textureResource.removeTag(myTag);
        }
    }
    textures.erase(std::remove(textures.begin(), textures.end(), texture), textures.end());
}

/*TextureManager::~TextureManager()
{
    LOG("should be 0:", (int)textures.size());
}*/