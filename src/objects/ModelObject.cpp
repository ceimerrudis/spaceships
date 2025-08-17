#include "ModelObject.h"
#include "Logger.h"
#include "WorldObject.h"
#include "GLerrorHandling.h"
#include <math.h>
#include <iostream>
#include <array>
#include "AdvancedMath.h"
#include "ObjectLoader.h"
#include "glad/glad.h"
#include "TextureManager.h"
#include "TextureResource.h"
#include <memory>

ModelObject::ModelObject(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib) 
:   D3Object(mesh, shaders, glResLib)
{
    normalIndexes = new unsigned int[trigCount];
    #if DEBUG_MEMORY
        LOG("created memory ", normalIndexes);
    #endif
    normalCount = meshP->normals.size();
    int n = meshP->normalIndices.size();
    if(n != trigCount * 3)
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
        normalIndexes[c] = meshP->normalIndices[i];
        c++;
    }

    normalsBufferKey = glResLib.CreateBuffer();
    normalIndexesBufferKey = glResLib.CreateBuffer();

    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *normalsBufferKey));
    GL(glBufferData(GL_SHADER_STORAGE_BUFFER       , normalCount * sizeof(float)         , meshP->normals.data()       , GL_STATIC_DRAW));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *normalsBufferKey));

    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, *normalIndexesBufferKey));
    GL(glBufferData(GL_SHADER_STORAGE_BUFFER       , trigCount * sizeof(unsigned int)      , normalIndexes , GL_STATIC_DRAW));
    GL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *normalIndexesBufferKey));

    GL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}

ModelObject::~ModelObject()
{

}
