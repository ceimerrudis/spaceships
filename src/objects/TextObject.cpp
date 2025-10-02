#include "TextObject.h"
#include "GLErrorHandling.h"
#include <glad/glad.h>
#include "glfw3.h" 
#include "TextData.h" 
#include <math.h> 
#include <memory> 

TextObject::TextObject(OpenGLResourceLibrary& glResLib, std::shared_ptr<Shader> shaders, std::shared_ptr<GlyphCache> glyphCache)
{
    InitRenderable(renderable, shaders, glResLib);
    InitUITransform(uiTransform);
    InitImageData(imageData, renderable);
    InitTextData(textData, renderable, glyphCache);
}

void TextObject::SetText(std::string newText, int size, std::weak_ptr<TextureManager> textureManager)
{
    ::SetText(textData, renderable, newText, size, textureManager);
}
