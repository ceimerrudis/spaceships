#include "Image.h"
#include <math.h>
#include <iostream>
#include <array>
#include "AdvancedMath.h"
#include "GLerrorHandling.h"
#include "glad/glad.h"
#include "TextureResource.h"
#include "TextureManager.h"

Image::Image(std::shared_ptr<Shader> shaders, TextureResource& textureResource, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib)
{
    entity.ID = -1;
    InitUITransform(uiTransform);
    InitRenderable(renderable, shaders, glResLib);
    InitImageData(imageData, renderable);
    imageData.textureKey = textureManager->AddTexture(GL_TEXTURE_2D, textureResource);
}

Image::~Image()
{
    
}

void Image::SetPosition()
{

}

void Image::SetAnchor(UIAnchor newAnchor)
{

}

void Image::SetSize()
{

}
