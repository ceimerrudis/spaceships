#include "Renderer.h"
#include "GLerrorHandling.h"

void Renderer::Render(Transform & transform, Renderable& renderrable, Shading& shading)
{
    GL(glUseProgram(*(renderrable.shaders->shaderKey)));
    Matrix<float, 3> inverseRotMat;
    inverseRotMat = transform.transformMatrix.ReduceDimensions();
    inverseRotMat = inverseRotMat.Inverse();
    Vector<float, 3> ldir = (inverseRotMat * lightDirtection).Normalized();
    
    renderrable.shaders->AssignDataToUniform(D3_LIGHT_DIRECTION, ldir.data);
    renderrable.shaders->AssignDataToUniform(D3_WORLD_TRANSFORM, transform.transformMatrix.data);
    GL(glBindVertexArray(*renderrable.vertexArrayObjectKey));
    
    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *shading.normalsBufferKey));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *shading.normalsBufferKey));
    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *shading.normalIndexesBufferKey));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *shading.normalIndexesBufferKey));
    
    GL(glDrawElements(GL_TRIANGLES, renderrable.trigCount*3, GL_UNSIGNED_INT, NULL));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0));
}

void Renderer::Render(Transform & transform, Renderable& renderrable, ModelTexture& modelTexture)
{
    GL(glUseProgram(*renderrable.shaders->shaderKey));
    GL(glDepthMask(GL_FALSE));
    GLuint tex = textureManager->LoadTexture(modelTexture.textureKey);
    renderrable.shaders->AssignDataToUniform(SKYBOX_TEXTURE_SLOT, &tex);
    GL(glBindVertexArray(*renderrable.vertexArrayObjectKey));
    GL(glDrawElements(GL_TRIANGLES, renderrable.trigCount * 3, GL_UNSIGNED_INT, NULL));

    GL(glDepthMask(GL_TRUE));
    GL(glBindVertexArray(0));
}

Vector<float, 2> Prime(float x, float y, float angleRadians, Vector<float, 2> pos)
{
    return Vector<float, 2>{
        std::cos(angleRadians) * (x - pos.x()) - std::sin(angleRadians) * (y - pos.y()) + pos.x(), 
        std::sin(angleRadians) * (x - pos.x()) + std::cos(angleRadians) * (y - pos.y()) + pos.y()
    };
}


void Renderer::Render(UITransform & transform, Renderable& renderrable, TextData& textData, ImageData& imageData)
{
    GL(glUseProgram(*renderrable.shaders->shaderKey));
    GL(glBindVertexArray(*renderrable.vertexArrayObjectKey));
    GL(glBindBuffer(GL_ARRAY_BUFFER, *renderrable.vertexBufferKey));//must bind to change data
    int n = textData.letterTextureKeys.size();
    float angleRadians = std::atan2(textData.textDir.y(), textData.textDir.x());
    for (size_t i = 0; i < n; i++)
    {
        float fofset = (2.0f * textData.letterTextureKeys[i].offset) / screenSize.x();
        float sizex = (2.0f * textData.letterTextureKeys[i].size.x()) / screenSize.x();
        float sizey = (2.0f * textData.letterTextureKeys[i].size.y()) / screenSize.y();
        
        Vector<float, 2> first = Prime(fofset+transform.position.x(),       transform.position.y(),        angleRadians, transform.position);
        Vector<float, 2> secon = Prime(fofset+transform.position.x(),       sizey+transform.position.y(),  angleRadians, transform.position);
        Vector<float, 2> third = Prime(fofset+sizex+transform.position.x(), sizey+transform.position.y(),  angleRadians, transform.position);
        Vector<float, 2> forth = Prime(fofset+sizex+transform.position.x(), transform.position.y(),        angleRadians, transform.position);

        imageData.vertexes = {
            first.x(), first.y(), 0, 0,
            secon.x(), secon.y(), 0, 1,
            third.x(), third.y(), 1, 1,
            forth.x(), forth.y(), 1, 0
        };

        GL(glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(float), imageData.vertexes.data()));
        
        int slot = textureManager->LoadTexture((textData.letterTextureKeys[i].textureKey));
        renderrable.shaders->AssignDataToUniform(TEXT_TEXTURE_SLOT, &slot);
        
        GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
    }

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Renderer::Render(UITransform & transform, Renderable& renderrable, ImageData& imageData)
{
    GL(glUseProgram(*renderrable.shaders->shaderKey));
    int slot = textureManager->LoadTexture(imageData.textureKey);
    renderrable.shaders->AssignDataToUniform(IMAGE_TEXTURE_SLOT, &slot);
    GL(glBindVertexArray(*renderrable.vertexArrayObjectKey));
    GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
    
    GL(glBindVertexArray(0));
}

void Renderer::SetLightDirection(Vector<float, 3> newLightDir)
{
    lightDirtection = newLightDir;
}

void Renderer::SetScreenSize(Vector<int, 2> newScreenSize)
{
    //TODO
    screenSize = newScreenSize;
}

Renderer::Renderer(std::shared_ptr<TextureManager> textureManager)
{
    this->textureManager = textureManager;
}

Renderer::~Renderer()
{}