#include "MeshData.h"
#include "GLErrorHandling.h"

void InitMeshData(MeshData& meshData, Renderable& renderable, const std::shared_ptr<solar::Mesh> mesh)
{
    #if DEBUG
        meshData.initialized = true;
    #endif
    meshData.meshP = mesh;
    renderable.trigCount = meshData.meshP->vertexIndices.size() / 3;
    renderable.vertexCount = meshData.meshP->vertices.size();
    
    GL(glBindVertexArray(*renderable.vertexArrayObjectKey));

    GL(glBindBuffer(GL_ARRAY_BUFFER, *renderable.vertexBufferKey));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *renderable.indexBufferKey));

    GL(glBufferData(GL_ARRAY_BUFFER         , renderable.vertexCount * sizeof(float)         , meshData.meshP->vertices.data()     , GL_STATIC_DRAW));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER , renderable.trigCount   * 3 * sizeof(unsigned int)  , meshData.meshP->vertexIndices.data()       , GL_STATIC_DRAW));

    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
}