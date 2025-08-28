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
    Vector<int, 2> size;
    int pixelHeight;
    Vector<int, 2> bearing;
    int advance;
    unsigned char* image;
};