#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "TextureResource.h"
#include "ObjectLoader.h"
#include "AssetLoader.h"
#include "Glyph.h"
#include <vector>
#include <memory>
#include <ft2build.h>
#include FT_FREETYPE_H


class GlyphCache{
public:
    Glyph& GetCharacter(unsigned int fontKey, char chr, int pixelHeight);
    Glyph& GetCharacter(unsigned int fontKey, char32_t chr, int pixelHeight);
    GlyphCache(AssetLoader& assetLoader);
    ~GlyphCache();
private:
    AssetLoader& assetLoader;//TODO fix
    std::vector<Glyph> glyphs;

    unsigned int lastFont;
    unsigned int lastSize;

    void LoadCharacter(unsigned int fontKey, char32_t chr, int pixelHeight);
};