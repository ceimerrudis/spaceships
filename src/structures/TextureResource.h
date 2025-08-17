#pragma once
#include "GlobalInclude.h"
#include <unordered_set>
#include <iostream>
#include <cstdint>

struct TextureResource {
    uint64_t resourceID;
    unsigned char* data = nullptr;
    int width;
    int height;
    int channels;

    inline TextureResource(uint64_t id, unsigned char* data, int width, int height, int channels) 
     : resourceID(id), 
     data(data),
     width(width),
     height(height),
     channels(channels)
    {
    }
};