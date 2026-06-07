#pragma once
#include <vector>

namespace cat 
{
struct Mesh{
    std::vector<char> name;
    std::vector<float> vertices;
    std::vector<unsigned int > vertexIndices;
    std::vector<unsigned int > normalIndices;
    std::vector<unsigned int > textureIndices;
    std::vector<float> normals;

    Mesh(unsigned int nameSize, unsigned int vertexSize, unsigned int indexSize, unsigned int normalsSize);
};
}