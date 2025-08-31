#include "Shading.h"
#include "GLErrorHandling.h"

void InitShading(Shading& shading, Renderable& renderable, MeshData& meshData, OpenGLResourceLibrary& glResLib)
{  
    #if DEBUG
        shading.initialized = true;
    #endif
    shading.normalIndexes = new unsigned int[renderable.trigCount];
    #if DEBUG_MEMORY
        LOG("created memory ", normalIndexes);
    #endif
    shading.normalCount = meshData.meshP->normals.size();
    int n = meshData.meshP->normalIndices.size();
    if(n != renderable.trigCount * 3)
    {
        error("Unexpectend normal index count!");
    }
    int c = 0;
    for (int i = 0; i < n; i+=3) {
        /*
        //get average
        meshP->normalIndices[i+0]
        meshP->normalIndices[i+1]
        meshP->normalIndices[i+2]
         */
        shading.normalIndexes[c] = meshData.meshP->normalIndices[i];
        c++;
    }

    shading.normalsBufferKey = glResLib.CreateBuffer();
    shading.normalIndexesBufferKey = glResLib.CreateBuffer();

    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *shading.normalsBufferKey));
    GL(glBufferData(GL_SHADER_STORAGE_BUFFER       , shading.normalCount * sizeof(float)         , meshData.meshP->normals.data()       , GL_STATIC_DRAW));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *shading.normalsBufferKey));

    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *shading.normalIndexesBufferKey));
    GL(glBufferData(GL_SHADER_STORAGE_BUFFER       , renderable.trigCount * sizeof(unsigned int)      , shading.normalIndexes , GL_STATIC_DRAW));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *shading.normalIndexesBufferKey));

    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}
