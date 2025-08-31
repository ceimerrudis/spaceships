#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "Letter.h"
#include "GlyphCache.h"
#include "Renderable.h"
#include "TextureManager.h"
#include <vector>
#include <memory>

//DYNAMIC SIZE
struct TextData
{
    #if DEBUG
        bool initialized;
    #endif
    Vector<float, 3> textDir;
    std::string text;
    int size;
    std::vector<Letter> letterTextureKeys;
    std::shared_ptr<GlyphCache> glyphCache;
};

void InitTextData(TextData& textData, Renderable& renderable, std::shared_ptr<GlyphCache> glyphCache);

void SetText(TextData& textData, Renderable& renderable, std::string newText, int size, std::weak_ptr<TextureManager> textureManager);

void SetDirection(TextData& textData, Vector<float, 3> direction);
