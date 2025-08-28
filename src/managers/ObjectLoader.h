#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <filesystem>

namespace solar{

struct Index
{
    unsigned int vertex;
    unsigned int normal;
    unsigned int texture;
};

struct Vertex{
    Vector<float, 3> position;
};

struct Mesh{
    std::vector<char> name;
    std::vector<float> vertices;
    std::vector<unsigned int > vertexIndices;
    std::vector<unsigned int > normalIndices;
    std::vector<unsigned int > textureIndices;
    std::vector<float> normals;

    Mesh(unsigned int nameSize, unsigned int vertexSize, unsigned int indexSize, unsigned int normalsSize);
};

class ObjectLoader
{
public:
    std::shared_ptr<Mesh> LoadObject(std::filesystem::path filePath);
};

}