#include "TextData.h"
#include "GLErrorHandling.h"
#include "TextureManager.h"

void InitTextData(TextData& textData, Renderable& renderable, std::shared_ptr<GlyphCache> glyphCache)
{
    #if DEBUG
        textData.initialized = true;
    #endif

    textData.textDir = Vector<float, 3> {1, 0, 0};
    textData.glyphCache = glyphCache; 

    textData.letterTextureKeys.clear();
};

void SetDirection(TextData& textData, Vector<float, 3> direction)
{
    textData.textDir = direction;
}


void SetText(TextData& textData,  Renderable& renderable, std::string newText, int size, std::weak_ptr<TextureManager> textureManager)
{
    textData.text = newText;
    textData.letterTextureKeys.clear();

    textData.size = size;
    int n = textData.text.length();
    int offset = 0;
    for (int i = 0; i < n; i++)
    {
        Glyph g = textData.glyphCache->GetCharacter(0, textData.text[i], size);
        TextureResource res
        {
            AssetLoader::GetResourceID(g.character), g.image, g.size.x(), g.size.y(), 1
        };

        std::shared_ptr<unsigned int> texKey;
        texKey = textureManager.lock()->AddTexture(GL_TEXTURE_2D, res);
        Letter letter;
        letter.offset = offset; 
        letter.textureKey = texKey;
        letter.size = g.size;
        textData.letterTextureKeys.push_back(letter);
        offset += g.advance;
    }

    //GL(glBindBuffer(GL_ARRAY_BUFFER, *(renderable.vertexBufferKey)));
    //GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(renderable.indexBufferKey)));
    //GL(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), textData., GL_STREAM_DRAW));
    //GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), textData., GL_STATIC_DRAW));
    //GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    //GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
    