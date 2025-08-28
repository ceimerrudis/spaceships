#include "AssetLoader.h"
#include <math.h>
#include "Logger.h"
#include "AdvancedMath.h"
#include "TextureResource.h"
#include "ObjectLoader.h"
#include <stb_image.h>
#include <filesystem>
#include <ft2build.h>
#include FT_FREETYPE_H

std::unordered_map<std::string, uint64_t>  AssetLoader::texResIds;
uint64_t AssetLoader::NextID = 0;

void AssetLoader::LoadObject(const std::string fileName)
{
    std::filesystem::path fullPath = std::filesystem::path("res/models/") / fileName;
    meshes.push_back(objectLoader.LoadObject(fullPath.string()));
}

void AssetLoader::LoadFont(const std::string fileName)
{
    std::filesystem::path fullPath = std::filesystem::path("res/fonts/") / fileName;

    FT_Face face;
    if (FT_New_Face(ft, fullPath.string().c_str(), 0, &face)) {
        error("Creating font face!");
    }
    fonts.push_back(face);
}

TaggedTextureResource& AssetLoader::GetResource(int id)
{
    return images[id];
}

int AssetLoader::LoadImage(const std::string fileName)
{
    int width;
    int height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    std::filesystem::path fullPath = std::filesystem::path("res/textures") / fileName;
    unsigned char* image = stbi_load(fullPath.string().c_str(), &width, &height, &channels, 0);
    if (!image) {
        error("Failed to load " + fileName + ": " + (std::string)stbi_failure_reason());
    }
    
    TaggedTextureResource tempTexRs(GetResourceID(fileName), image, width, height, channels);
    images.push_back(tempTexRs);

    return (int)images.size()-1;
}

AssetLoader::AssetLoader()
{
    if (FT_Init_FreeType(&ft)) {
        error("Cant initialize font engine!");
    }
}

AssetLoader::~AssetLoader()
{
    for (TaggedTextureResource image : images)
    {
        if(!image.isTagged())
        {   
            stbi_image_free(image.data); 
        }
        else
        {
            LOG("Offending tags");
            for (const std::string& tag : image.tags) {
                LOG(tag);
            }
            error("Tag has not been released. Tags logged in log");
        }
    }
}

uint64_t AssetLoader::GetResourceID(const std::string& filename)
{
    auto iterator = texResIds.find(filename);
    if(iterator != texResIds.end())
    {
        return iterator->second;
    }

    texResIds.emplace(filename, NextID);
    NextID++;
    return NextID-1;
}

uint64_t AssetLoader::GetResourceID(const char32_t& chr)
{
    std::string chrText;
    for(int i = 0; i < 4; i++)
    {
        char byte = static_cast<char>((chr >> (i * 8)) & 0xFF);
        chrText += byte;
    }
    return GetResourceID(chrText);
}