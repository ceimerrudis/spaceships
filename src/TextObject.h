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
    TextObject(OpenGLResourceLibrary& glResLib, std::shared_ptr<Shader> shaders, std::string text, int size, vector2 pos, vector3 dir, std::shared_ptr<TextureManager> textureManager, GlyphCache& glyphCache);

    void Render() override;

    std::string GetText();
    void SetText(std::string newText);
    vector2i screenSize;
private:
    std::array<float, 16> vertexes;
    std::array<unsigned int, 6> indicies;
    vector3 textDir;
    

    std::string text;
    int size;
    std::vector<Letter> letterTextureKeys;
    GlyphCache& glyphCache;

    vector2 pos;
};
