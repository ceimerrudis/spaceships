#include "TextObject.h"
#include "GLerrorHandling.h"
#include <glad/glad.h>
#include "glfw3.h" 
#include <math.h> 
#include <memory> 

TextObject::TextObject(OpenGLResourceLibrary& glResLib, std::shared_ptr<Shader> shaders, std::string text, int size, vector2 pos, vector3 dir, std::shared_ptr<TextureManager> textureManager, GlyphCache& glyphCache)
:   Renderable(shaders, glResLib),
    glyphCache(glyphCache)
{
    this->textureManager = textureManager;
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

    SetText(text);
}

vector2 Prime(float x, float y, float angleRadians, vector2 pos)
{
    return vector2{
        std::cos(angleRadians) * (x - pos.x()) - std::sin(angleRadians) * (y - pos.y()) + pos.x(), 
        std::sin(angleRadians) * (x - pos.x()) + std::cos(angleRadians) * (y - pos.y()) + pos.y()
    };
}

void TextObject::Render()
{
    //TODO 3d text
    GL(glUseProgram(*shaders->shaderKey));
    
    GL(glBindVertexArray(*vertexArrayObjectKey));
    GL(glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferKey));//must bind to change data
    int n = letterTextureKeys.size();
    float angleRadians = std::atan2(textDir.y(), textDir.x());
    for (size_t i = 0; i < n; i++)
    {
        float fofset = (2.0f * letterTextureKeys[i].offset) / screenSize.x();
        float sizex = (2.0f * letterTextureKeys[i].size.x()) / screenSize.x();
        float sizey = (2.0f * letterTextureKeys[i].size.y()) / screenSize.y();
        
        vector2 first = Prime(fofset+pos.x(),       pos.y(),        angleRadians, pos);
        vector2 secon = Prime(fofset+pos.x(),       sizey+pos.y(),  angleRadians, pos);
        vector2 third = Prime(fofset+sizex+pos.x(), sizey+pos.y(),  angleRadians, pos);
        vector2 forth = Prime(fofset+sizex+pos.x(), pos.y(),        angleRadians, pos);

        vertexes = {
            first.x(), first.y(), 0, 0,
            secon.x(), secon.y(), 0, 1,
            third.x(), third.y(), 1, 1,
            forth.x(), forth.y(), 1, 0
        };

        GL(glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(float), vertexes.data()));
        
        int slot = textureManager->LoadTexture((letterTextureKeys[i].textureKey));
        shaders->AssignDataToUniform(TEXT_TEXTURE_SLOT, &slot);
        
        GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
    }

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

std::string TextObject::GetText()
{
    return text;
}

void TextObject::SetText(std::string newText)
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
        texKey = textureManager->AddTexture(GL_TEXTURE_2D, res);
        Letter letter;
        letter.offset = offset; 
        letter.textureKey = texKey;
        letter.size = g.size;
        letterTextureKeys.push_back(letter);
        offset += g.advance;
    }
}