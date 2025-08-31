#pragma once
#include "GlobalInclude.h"
#include "TextObject.h"
#include "CubemapObject.h"
#include "TaggedTextureResource.h"
#include <vector>
#include <array>
#include <unordered_set>
#include "OpenGLResourceLibrary.h"
#include "Shading.h"
#include "ModelTexture.h"

class Renderer{
private:
    Vector<float, 3> lightDirtection;
    Vector<int, 2> screenSize;
    std::shared_ptr<TextureManager> textureManager;
public:
    void Render(Transform & transform, Renderable& renderrable, Shading& shading);

    void Render(Transform & transform, Renderable& renderrable, ModelTexture& modelTexture);
    
    void Render(UITransform & transform, Renderable& renderrable, TextData& textData, ImageData& imageData);

    void Render(UITransform & transform, Renderable& renderrable, ImageData& imageData);

    void SetLightDirection(Vector<float, 3> newLightDir);

    void SetScreenSize(Vector<int, 2> newScreenSize);

    Renderer(std::shared_ptr<TextureManager> textureManager);

    ~Renderer();
};
