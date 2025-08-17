#include "ObjectLoader.h"

using namespace solar;

Mesh::Mesh(unsigned int nameSize, unsigned int vertexSize, unsigned int indexSize, unsigned int normalsCount)
:   name(nameSize),
    vertices(vertexSize),
    vertexIndices(indexSize),
    normalIndices(indexSize),
    textureIndices(indexSize),
    normals(normalsCount*4)
{}

std::shared_ptr<Mesh> ObjectLoader::LoadObject(std::filesystem::path filePath)
{   
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        error("Failed to open file: " + filePath.string());
    }

    std::string line;
    std::string modelName;
    std::vector<Index> indices;
    std::vector<Vertex> vertices;
    std::vector<vector3> normals;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') // Skip empty lines and comments
            continue;

        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "o")
        {
            iss >> modelName;
        }
        else if (prefix == "v")
        {
            vector3 pos;
            iss >> pos.x() >> pos.y() >> pos.z();
            vertices.push_back(Vertex{ pos });
        }
        else if (prefix == "vn")
        {
            vector3 normal;
            iss >> normal.x() >> normal.y() >> normal.z();
            normals.push_back(normal);
        }
        else if (prefix == "vt")
        {
            // Texture coords (leave blank)
        }
        else if (prefix == "f")
        {
            // Face definition: can be triangles or quads or more
            // Each face vertex can be like: v, v/vt, v//vn, v/vt/vn
            // We'll parse indices for vertex, texture, normal separately

            std::vector<Index> faceIndices;

            std::string vertexStr;
            while (iss >> vertexStr)
            {
                Index idx = { 0, 0, 0 }; // Initialize with zero

                // Parse something like "v/vt/vn", "v//vn", "v/vt", or just "v"
                size_t firstSlash = vertexStr.find('/');
                size_t lastSlash = vertexStr.rfind('/');

                if (firstSlash == std::string::npos)
                {
                    idx.vertex = std::stoi(vertexStr);
                }
                else if (firstSlash == lastSlash)
                {
                    // v/vt
                    idx.vertex = std::stoi(vertexStr.substr(0, firstSlash));
                    std::string afterSlash = vertexStr.substr(firstSlash + 1);
                    idx.texture = std::stoi(afterSlash);
                }
                else
                {
                    // v//vn
                    idx.vertex = std::stoi(vertexStr.substr(0, firstSlash));
                    if (firstSlash + 1 != lastSlash)
                    {
                        // v/vt/vn
                        idx.texture = std::stoi(vertexStr.substr(firstSlash + 1, lastSlash - firstSlash - 1));
                    }
                    std::string normalStr = vertexStr.substr(lastSlash + 1);
                    idx.normal = std::stoi(normalStr);
                }

                // OBJ indices are 1-based, convert to 0-based
                if (idx.vertex > 0) idx.vertex--;
                if (idx.normal > 0) idx.normal--;
                if (idx.texture > 0) idx.texture--;

                faceIndices.push_back(idx);
            }

            int n = faceIndices.size() - 1;
            for(int i = 1; i < n; i++)
            {
                indices.push_back(faceIndices[0]);
                indices.push_back(faceIndices[i]);
                indices.push_back(faceIndices[i+1]);
            }
        }
        else if (prefix == "s")
        {
            // Smoothing groups (leave blank)
        }
        else if (prefix == "mtllib")
        {
            // Material library (leave blank)
        }
        else if (prefix == "usemtl")
        {
            // which mat to use (leave blank)
        }
        else
        {
            LOG("Unknown prefix: " + prefix);
        }
    }

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(modelName.size(), vertices.size()*3, indices.size(), normals.size());

    int n = std::max(
            std::max(modelName.size(), vertices.size()),
            std::max(indices.size(), normals.size()));

    for (int i = 0; i < n; i++)
    {
        if(modelName.size() > i)
        {
            mesh->name[i] = modelName[i];
            if(modelName.size() > i+1)
            {
                mesh->name[i+1] = '\0';
            }
        }
        if(vertices.size() > i)
        {
            mesh->vertices[i*3+0] = vertices[i].position.x();
            mesh->vertices[i*3+1] = vertices[i].position.y();
            mesh->vertices[i*3+2] = vertices[i].position.z();
        }
        if(indices.size() > i)
        {
            mesh->vertexIndices[i] = indices[i].vertex;
            mesh->normalIndices[i] = indices[i].normal;
            mesh->textureIndices[i] = indices[i].texture;
        }
        if(normals.size() > i)
        {
            mesh->normals[i*4+0] = normals[i].x();
            mesh->normals[i*4+1] = normals[i].y();
            mesh->normals[i*4+2] = normals[i].z();
            mesh->normals[i*4+3] = 0;//padding for 16 bit stride as requested by SSBO
        }
    }

    return mesh;
}