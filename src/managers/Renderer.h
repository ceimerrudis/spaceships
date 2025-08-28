#pragma once
#include "GlobalInclude.h"
#include "TextObject.h"
#include "ModelObject.h"
#include "CubemapObject.h"
#include "D2Object.h"
#include "TaggedTextureResource.h"
#include <vector>
#include <array>
#include <unordered_set>
#include "OpenGLResourceLibrary.h"

class Renderer{
private:
    Vector<float, 3> lightDirtection;
    Vector<int, 2> screenSize;
    std::shared_ptr<TextureManager> textureManager;
public:
    void Render(ModelObject* model);

    void Render(CubemapObject* cubemap);
    
    void Render(TextObject* text);

    void Render(D2Object* d2Obj);

    void SetLightDirection(Vector<float, 3> newLightDir);

    void SetScreenSize(Vector<int, 2> newScreenSize);

    Renderer(std::shared_ptr<TextureManager> textureManager);

    ~Renderer();
};
