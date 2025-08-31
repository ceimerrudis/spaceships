#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "TextureManager.h"
#include "Renderable.h"
#include "ImageData.h"
#include "UITransform.h"
#include <array>
#include "Entity.h"

class Image
{
public:
    Entity entity;
    UITransform uiTransform;
    Renderable renderable;
    ImageData imageData;

    Image(std::shared_ptr<Shader> shaders, TextureResource& textureResource, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib);
    
    ~Image();

    void SetPosition();

    void SetAnchor(UIAnchor newAnchor);

    void SetSize();
};