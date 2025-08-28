#include "WorldObject.h"
#include <math.h>
#include <iostream>
#include <array>
#include "AdvancedMath.h"
#include "GLerrorHandling.h"
#include "glad/glad.h"
#include "D2Object.h"
#include "TextureResource.h"
#include "TextureManager.h"

D2Object::D2Object(std::shared_ptr<Shader> shaders, Vector<float, 2> bottomLeft, Vector<float, 2> topRight, TextureResource& textureResource, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib)
    :   Renderable(shaders, glResLib)
{
    unsigned int indicies[6] = {0, 3, 1, 3, 2, 1};
    vertexes = //Pirmas 2 kolonas ir vertex position  uotras 2 texturu koordinates
    {
         bottomLeft.x(),   bottomLeft.y(),    0, 0,
         bottomLeft.x(),   topRight.y(),      0, 1,
         topRight.x(),     topRight.y(),      1, 1,
         topRight.x(),     bottomLeft.y(),    1, 0
    };

    GL(glBindVertexArray(*vertexArrayObjectKey));

    GL(glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferKey));
    GL(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), vertexes.data(), GL_STATIC_DRAW));

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferKey));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));

    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
    GL(glEnableVertexAttribArray(1));
    GL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float))));
    
    textureKey = textureManager->AddTexture(GL_TEXTURE_2D, textureResource);

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
    GL(glDisableVertexAttribArray(1));
}

D2Object::~D2Object()
{
    
}