#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "TaggedTextureResource.h"
#include "ObjectLoader.h"
#include <vector>
#include <memory>
#include <ft2build.h>
#include <unordered_map>
#include FT_FREETYPE_H

struct AssetLoader{
    std::vector<TaggedTextureResource> images;
    std::vector<std::shared_ptr<solar::Mesh>> meshes;
    std::vector<FT_Face> fonts;
    solar::ObjectLoader objectLoader;
    static std::unordered_map<std::string, uint64_t> texResIds;
    static uint64_t NextID;
    FT_Library ft;

    TaggedTextureResource& GetResource(int id);

    static uint64_t GetResourceID(const std::string& filename);

    static uint64_t GetResourceID(const char32_t& chr);

    int LoadImage(const std::string fileName);

    void LoadObject(const std::string fileName);

    void LoadFont(const std::string fileName);

    AssetLoader();

    ~AssetLoader();
};