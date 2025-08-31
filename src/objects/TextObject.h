#pragma once
#include "GlobalInclude.h"
#include "Glyph.h"
#include "TextureResource.h"
#include "TextureManager.h"
#include "GlyphCache.h"
#include "Letter.h"
#include "Entity.h"
#include "TextData.h"
#include "ImageData.h"
#include "Renderable.h" 
#include "UITransform.h"
#include <vector>
#include <memory>

class TextObject
{
public:
    Entity entity;
    ImageData imageData;
    TextData textData;
    UITransform uiTransform;
    Renderable renderable;

    TextObject(OpenGLResourceLibrary& glResLib, std::shared_ptr<Shader> shaders, std::shared_ptr<GlyphCache> glyphCache);
    
    void SetText(std::string newText, int size, std::weak_ptr<TextureManager> textureManager);
};
