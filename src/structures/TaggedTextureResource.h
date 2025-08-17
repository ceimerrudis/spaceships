#pragma once
#include "GlobalInclude.h"
#include "TextureResource.h"
#include <unordered_set>
#include <iostream>

//Must only be used (stored) in asset loader
struct TaggedTextureResource : TextureResource {
    std::unordered_set<std::string> tags;

    inline TaggedTextureResource(uint64_t id, unsigned char* data, int width, int height, int channels) 
     : TextureResource(id, data, width, height, channels)
    {
    }

    inline bool isTagged() const {
        return !tags.empty();
    }

    inline void addTag(const std::string& tag) {
        tags.insert(tag);
    }

    inline void removeTag(const std::string& tag) {
        tags.erase(tag);
    }
};