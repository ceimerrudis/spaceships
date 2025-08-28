#pragma once
#include "GlobalInclude.h"
#include "Glyph.h"
#include "TextureResource.h"
#include "TextureManager.h"
#include "GlyphCache.h"
#include "D2Object.h"
#include "Letter.h"
#include <vector>
#include <memory>

class TextObject : public Renderable
{
public:
    TextObject(OpenGLResourceLibrary& glResLib, std::shared_ptr<Shader> shaders, int size, Vector<float, 2> pos, Vector<float, 3> dir, GlyphCache& glyphCache);

    ~TextObject() override;

    std::string GetText();
    
    void SetText(std::string newText, std::weak_ptr<TextureManager> textureManager);

    std::array<float, 16> vertexes;
    std::array<unsigned int, 6> indicies;
    Vector<float, 3> textDir;

    std::string text;
    int size;
    std::vector<Letter> letterTextureKeys;
    GlyphCache& glyphCache;

    Vector<float, 2> pos;
};
