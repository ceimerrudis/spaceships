#include "DebugDraw.h"
#include "ShaderManaging.h"
#include <vector>

DebugDraw::DebugDraw(std::vector<float> vert, const matrix4 projMat, vector3 color)
{
    this->line = true;    
    shaderKey = LoadShaderDEBUG("debug_line_vertex.glsl", "debug_line_fragment.glsl");
    glUseProgram(shaderKey);
    GL(projMatUniformLoc = glGetUniformLocation(shaderKey, "u_projMatrix"));
    GL(viewMatUniformLoc = glGetUniformLocation(shaderKey, "u_observerPlane"));
    GL(worldTransfUniformLoc = glGetUniformLocation(shaderKey, "u_worldPlaneTransf"));
    GL(colorLoc = glGetUniformLocation(shaderKey, "u_color"));
    glUniform3f(colorLoc, color.x(), color.y(), color.z());
    glUniformMatrix4fv(projMatUniformLoc, 1, GL_TRUE, projMat.data);
    glUseProgram(0);
    vertexCount = vert.size();
    GL(glGenBuffers(1, &vertexBufferKey)); 
    GL(glGenVertexArrays(1, &vertexArrayObjectKey));

    GL(glBindVertexArray(vertexArrayObjectKey));

    GL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferKey));

    GL(glBufferData(GL_ARRAY_BUFFER         , vertexCount * sizeof(float)         , vert.data()     , GL_STATIC_DRAW));

    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
}

DebugDraw::DebugDraw(std::vector<float> vert, std::vector<unsigned int> incdic, const matrix4 projMat, vector3 color)
{
    this->line = false;    
    shaderKey = LoadShaderDEBUG("debug_vertex.glsl", "debug_fragment.glsl");
    glUseProgram(shaderKey);
    GL(projMatUniformLoc = glGetUniformLocation(shaderKey, "u_projMatrix"));
    GL(viewMatUniformLoc = glGetUniformLocation(shaderKey, "u_observerPlane"));
    GL(worldTransfUniformLoc = glGetUniformLocation(shaderKey, "u_worldPlaneTransf"));
    GL(colorLoc = glGetUniformLocation(shaderKey, "u_color"));
    glUniform3f(colorLoc, color.x(), color.y(), color.z());
    glUniformMatrix4fv(projMatUniformLoc, 1, GL_TRUE, projMat.data);
    glUseProgram(0);

    GL(glGenBuffers(1, &vertexBufferKey)); 
    GL(glGenBuffers(1, &indexBufferKey));
    GL(glGenVertexArrays(1, &vertexArrayObjectKey));

    trigCount = incdic.size() / 3;
    vertexCount = vert.size();
    
    GL(glBindVertexArray(vertexArrayObjectKey));

    GL(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferKey));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferKey));

    GL(glBufferData(GL_ARRAY_BUFFER         , vertexCount * sizeof(float)         , vert.data()     , GL_STATIC_DRAW));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER , trigCount   * 3 * sizeof(unsigned int)  , incdic.data()       , GL_STATIC_DRAW));

    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
}

void DebugDraw::Render(const matrix4 translationMat, const matrix4 viewMat)
{
    this->translationMat = translationMat;
    GL(glUseProgram(shaderKey));
    
    glUniformMatrix4fv(viewMatUniformLoc, 1, GL_TRUE, viewMat.data);
    glUniformMatrix4fv(worldTransfUniformLoc, 1, GL_TRUE, translationMat.data);
    GL(glBindVertexArray(vertexArrayObjectKey));
    
    if(line)
    {
        glDrawArrays(GL_LINES, 0, 2);
    }
    else{
        GL(glDrawElements(GL_TRIANGLES, trigCount*3, GL_UNSIGNED_INT, NULL));
    }

    GL(glBindVertexArray(0));
}


DebugDraw::~DebugDraw()
{
    GL(glDeleteProgram(shaderKey));
    GL(glDeleteVertexArrays(1, &vertexArrayObjectKey));
    GL(glDeleteBuffers(1, &vertexBufferKey));
    if(!line){
        GL(glDeleteBuffers(1, &indexBufferKey));
    }
}
