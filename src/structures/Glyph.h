#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "TextureResource.h"
#include "ObjectLoader.h"
#include <vector>
#include <memory>
#include <ft2build.h>
#include FT_FREETYPE_H


struct Glyph{
    unsigned int fontKey;
    char32_t character;
    vector2i size;
    int pixelHeight;
    vector2i bearing;
    int advance;
    unsigned char* image;
};