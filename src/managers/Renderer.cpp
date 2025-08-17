#include "Renderer.h"
#include "GLerrorHandling.h"

void Renderer::Render(ModelObject* model)
{
    GL(glUseProgram(*model->shaders->shaderKey));
    lightDirtection = {1,1,0};
    lightDirtection = lightDirtection.Normalized();
    LOG(lightDirtection);
    matrix3 inverseRotMat;
    inverseRotMat = model->translationMat.Inverse();

    vector3 ldir = VecMultipliedByMatrix(lightDirtection, inverseRotMat).Normalized();
    LOG("transl ", model->translationMat);
    LOG(ldir);
    model->shaders->AssignDataToUniform(D3_LIGHT_DIRECTION, ldir.data);
    model->shaders->AssignDataToUniform(D3_WORLD_TRANSFORM, model->translationMat.data);
    GL(glBindVertexArray(*model->vertexArrayObjectKey));
    
    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *model->normalsBufferKey));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *model->normalsBufferKey));
    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *model->normalIndexesBufferKey));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *model->normalIndexesBufferKey));
    
    GL(glDrawElements(GL_TRIANGLES, model->trigCount*3, GL_UNSIGNED_INT, NULL));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0));
}

void Renderer::Render(CubemapObject* cubemap)
{
    GL(glUseProgram(*cubemap->shaders->shaderKey));
    GL(glDepthMask(GL_FALSE));
    GLuint tex = textureManager->LoadTexture(cubemap->textureKey);
    cubemap->shaders->AssignDataToUniform(SKYBOX_TEXTURE_SLOT, &tex);
    GL(glBindVertexArray(*cubemap->vertexArrayObjectKey));
    GL(glDrawElements(GL_TRIANGLES, cubemap->trigCount*3, GL_UNSIGNED_INT, NULL));

    GL(glDepthMask(GL_TRUE));
    GL(glBindVertexArray(0));
}

vector2 Prime(float x, float y, float angleRadians, vector2 pos)
{
    return vector2{
        std::cos(angleRadians) * (x - pos.x()) - std::sin(angleRadians) * (y - pos.y()) + pos.x(), 
        std::sin(angleRadians) * (x - pos.x()) + std::cos(angleRadians) * (y - pos.y()) + pos.y()
    };
}

void Renderer::Render(TextObject* text)
{
    GL(glUseProgram(*text->shaders->shaderKey));
    GL(glBindVertexArray(*text->vertexArrayObjectKey));
    GL(glBindBuffer(GL_ARRAY_BUFFER, *text->vertexBufferKey));//must bind to change data
    int n = text->letterTextureKeys.size();
    float angleRadians = std::atan2(text->textDir.y(), text->textDir.x());
    for (size_t i = 0; i < n; i++)
    {
        float fofset = (2.0f * text->letterTextureKeys[i].offset) / screenSize.x();
        float sizex = (2.0f * text->letterTextureKeys[i].size.x()) / screenSize.x();
        float sizey = (2.0f * text->letterTextureKeys[i].size.y()) / screenSize.y();
        
        vector2 first = Prime(fofset+text->pos.x(),       text->pos.y(),        angleRadians, text->pos);
        vector2 secon = Prime(fofset+text->pos.x(),       sizey+text->pos.y(),  angleRadians, text->pos);
        vector2 third = Prime(fofset+sizex+text->pos.x(), sizey+text->pos.y(),  angleRadians, text->pos);
        vector2 forth = Prime(fofset+sizex+text->pos.x(), text->pos.y(),        angleRadians, text->pos);

        text->vertexes = {
            first.x(), first.y(), 0, 0,
            secon.x(), secon.y(), 0, 1,
            third.x(), third.y(), 1, 1,
            forth.x(), forth.y(), 1, 0
        };

        GL(glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(float), text->vertexes.data()));
        
        int slot = textureManager->LoadTexture((text->letterTextureKeys[i].textureKey));
        text->shaders->AssignDataToUniform(TEXT_TEXTURE_SLOT, &slot);
        
        GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
    }

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Renderer::Render(D2Object* d2Obj)
{
    GL(glUseProgram(*d2Obj->shaders->shaderKey));
    int slot = textureManager->LoadTexture(d2Obj->textureKey);
    d2Obj->shaders->AssignDataToUniform(IMAGE_TEXTURE_SLOT, &slot);
    GL(glBindVertexArray(*d2Obj->vertexArrayObjectKey));
    GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
    
    GL(glBindVertexArray(0));
}

void Renderer::SetLightDirection(vector3 newLightDir)
{
    lightDirtection = newLightDir;
}

void Renderer::SetScreenSize(vector2i newScreenSize)
{
    screenSize = newScreenSize;
}

Renderer::Renderer(std::shared_ptr<TextureManager> textureManager)
{
    this->textureManager = textureManager;
}

Renderer::~Renderer()
{}