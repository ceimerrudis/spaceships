#include "TextObject.h"
#include "GLerrorHandling.h"
#include <glad/glad.h>
#include "glfw3.h" 
#include <math.h> 
#include <memory> 

TextObject::TextObject(OpenGLResourceLibrary& glResLib, std::shared_ptr<Shader> shaders, int size, vector2 pos, vector3 dir, GlyphCache& glyphCache)
:   Renderable(shaders, glResLib),
    glyphCache(glyphCache)
{
    GL(glBindVertexArray(*vertexArrayObjectKey));

    GL(glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferKey));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferKey));

    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
    GL(glEnableVertexAttribArray(1));
    GL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float))));

    letterTextureKeys.clear();
    this->size = size;
    this->pos = pos;
    this->textDir = dir;

    indicies = {0, 3, 1, 3, 2, 1};
    
    GL(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), nullptr, GL_STREAM_DRAW));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
    GL(glDisableVertexAttribArray(1));
}

TextObject::~TextObject()
{
    
}

std::string TextObject::GetText()
{
    return text;
}

void TextObject::SetText(std::string newText, std::weak_ptr<TextureManager> textureManager)
{
    text = newText;
    letterTextureKeys.clear();

    int n = text.length();
    int offset = 0;
    for (int i = 0; i < n; i++)
    {
        Glyph g = glyphCache.GetCharacter(0, text[i], size);
        TextureResource res{AssetLoader::GetResourceID(g.character), g.image, g.size.x(), g.size.y(), 1};
        std::shared_ptr<unsigned int> texKey;
        texKey = textureManager.lock()->AddTexture(GL_TEXTURE_2D, res);
        Letter letter;
        letter.offset = offset; 
        letter.textureKey = texKey;
        letter.size = g.size;
        letterTextureKeys.push_back(letter);
        offset += g.advance;
    }
}