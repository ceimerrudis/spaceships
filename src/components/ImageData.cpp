#include "ImageData.h"
#include "AdvancedMath.h"
#include "GLErrorHandling.h"
#include <array>

void InitImageData(ImageData& imageData, Renderable& renderable, bool IsText)
{
    Vector<float, 2> bottomLeft;
    Vector<float, 2> topRight;
    unsigned int indicies[6] = {0, 3, 1, 3, 2, 1};
    imageData.vertexes = //Pirmas 2 kolonas ir vertex position  uotras 2 texturu koordinates
    {
         bottomLeft.x(),   bottomLeft.y(),    0, 0,
         bottomLeft.x(),   topRight.y(),      0, 1,
         topRight.x(),     topRight.y(),      1, 1,
         topRight.x(),     bottomLeft.y(),    1, 0
    };

    GL(glBindVertexArray(*renderable.vertexArrayObjectKey));
    GL(glBindBuffer(GL_ARRAY_BUFFER, *renderable.vertexBufferKey));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *renderable.indexBufferKey));
    
    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
    GL(glEnableVertexAttribArray(1));
    GL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float))));

    if(IsText)
    {
        GL(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), imageData.vertexes.data(), GL_STREAM_DRAW));
    }
    else
    {
        GL(glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), imageData.vertexes.data(), GL_STATIC_DRAW));
    }
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
    GL(glDisableVertexAttribArray(1));
}