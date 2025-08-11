#include "GlyphCache.h"

Glyph& GlyphCache::GetCharacter(unsigned int fontKey, char chr, int pixelHeight)
{
    lastFont = -1;
    lastSize = -1;
    char32_t ch = chr;
    return GetCharacter(fontKey, ch, pixelHeight);
}

Glyph& GlyphCache::GetCharacter(unsigned int fontKey, char32_t chr, int pixelHeight)
{
    int n = glyphs.size();
    for (int i = 0; i < n; i++)
    {
        if(fontKey == glyphs[i].fontKey && chr == glyphs[i].character && pixelHeight == glyphs[i].size.y())
        {
            return glyphs[i];
        }
    }
    
    LoadCharacter(fontKey, chr, pixelHeight);
    return glyphs[glyphs.size()-1];
}

void GlyphCache::LoadCharacter(unsigned int fontKey, char32_t chr, int pixelHeight)
{
    FT_Face& font = assetLoader.fonts[fontKey];
    //FT_Select_Charmap(font, FT_ENCODING_UNICODE);
    FT_Set_Charmap(font, font->charmaps[0]);
    if(lastSize != pixelHeight || lastFont != fontKey){
        FT_Set_Pixel_Sizes(font, 0, pixelHeight);
        lastSize = pixelHeight;
        lastFont = fontKey;
    }
    if (FT_Load_Char(font, chr, FT_LOAD_RENDER)) {
        error("failed to load charachters");
    }

    FT_GlyphSlot g = font->glyph;
    int width = g->bitmap.width;
    int height = g->bitmap.rows;
    
    Glyph glyph;
    glyph.fontKey = fontKey;
    glyph.character = chr;
    glyph.size = vector2i{width, height};
    glyph.bearing = vector2i{g->bitmap_left, g->bitmap_top};
    glyph.advance = g->advance.x >> 6;
    glyph.image = new unsigned char[width*height];
    for (int y = 0; y < height; ++y) {
        memcpy(
            glyph.image + y * width,
            g->bitmap.buffer + (height - 1 - y) * width,
            width
        );
    }
    glyphs.push_back(glyph);
}

GlyphCache::GlyphCache(AssetLoader& assetLoader) : assetLoader(assetLoader)
{

}

GlyphCache::~GlyphCache()
{
    int n = glyphs.size();
    for (int i = 0; i < n; i++)
    {
        delete[] glyphs[i].image;
    }
}