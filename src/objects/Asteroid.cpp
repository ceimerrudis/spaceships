#include "Asteroid.h"
#include "glad/glad.h"
#include "GLerrorHandling.h"
#include "PhysicsSystem.h"
#include "Game.h"
#include "Random.h"
#include <algorithm>
#include <map>
#include "Debugger.h"

Asteroid::Asteroid(unsigned int id, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib, PhysicsSystem& physSys)
:   ModelObject(GenAsteroid(id), shaders, glResLib),
    id(id)
{
    position = {RandomF(100, 200), RandomF(100, 200), RandomF(100, 200)};
    updateTranslationMat();
    //position TODO gen randomly
    //physSys.AddCollider(id, position, {1.0f, 1.0f, 1.0f});
}

void Asteroid::update(Game* game)
{
    //Does whatewer a rock does
    rotate(up, 0.01);
    //move(forward * (float(this->throttle) / 1000));
    //move(right * (float(this->aiMoveRight) / 10));
    //move(up * (float(this->aiMoveUp) / 10));
    //    
    //rotate(up, aiYaw / -50);
    //rotate(forward, aiRoll / 50);
    //rotate(right, aiPitch / 50);
}

Asteroid::~Asteroid()
{
    
}

struct Face
{
    int p1;
    int p2;
    int p3;
};

struct Edge {
    int a, b;
    Face oldFace;
    
    Edge(int x, int y) {
        if (x < y) {
            a = x; b = y;
        } else {
            a = y; b = x;
        }
    }

    bool operator==(const Edge& other) const {
        return a == other.a && b == other.b;
    }

    bool operator<(const Edge& other) const {
        return std::tie(a, b) < std::tie(other.a, other.b);
    }

    Edge(int a, int b, Face f)
    {
        this->a = a;
        this->b = b;
        this->oldFace = f;
    }
};

bool AreCoplanar(vector3 p1, vector3 p2, vector3 p3, vector3 p4);
bool CanFaceSeePoint(vector3* vertexes, Face f, vector3 p);

bool CanFaceSeePoint(vector3 p1, vector3 p2, vector3 p3, vector3 pointToCheck)
{
    vector3 cross = (p3-p1) * (p2-p1);
    vector3 toPoint = pointToCheck - p1;
    return toPoint % cross > 0.000001;
}


std::shared_ptr<solar::Mesh> Asteroid::GenAsteroid(unsigned int id)
{

    std::string name = "Rand_asteroid_"+std::to_string(id);
    
    int vertexSize = RandomI(10, 20);
    vector3* verticies = new vector3[vertexSize];
    
    for (int i = 0; i < vertexSize; i++)
    {
        verticies[i] = {RandomF(-20, 20), RandomF(-20, 20), RandomF(-20, 20)};
    }
    
    std::vector<Face> faces;
    std::vector<std::pair<int, std::vector<int>>> conflictGraph;

    int D = 3;
    while(AreCoplanar(verticies[0], verticies[1], verticies[2], verticies[D])){D++;}
    
    int A = 0, B = 1, C = 2;
    vector3 normal = (verticies[B] - verticies[A]) * (verticies[C] - verticies[A]);
    float orientation = (verticies[D] - verticies[A]) % normal;
    if(orientation < 0)
    {
        int s = C;
        C = B;
        B = s;
        faces.push_back({A, B, C});
    }
    else
    {
        faces.push_back({A, B, C});
    }
    faces.push_back({A, C, D});
    faces.push_back({C, B, D});
    faces.push_back({B, A, D});

    int fcount = faces.size();
    for (int i = 3; i < vertexSize; i++)//For each point left
    {
        if(i == D)
        {
            continue;
        }
        for (int j = 0; j < fcount; j++)// Go through each face and find conflicts
        {
            if(CanFaceSeePoint(verticies, faces[j], verticies[i]))
            {
                std::vector<std::pair<int, std::vector<int>>>::iterator it
                 = std::find_if(conflictGraph.begin(), conflictGraph.end(), 
                 [i](const std::pair<int, std::vector<int>>& p) { return p.first == i; });

                if (it == conflictGraph.end()) {
                    conflictGraph.push_back({i, {j}});
                } else {
                    it->second.push_back(j);
                }
            }
        }
    }

    for (int i = 0; i < conflictGraph.size(); i)//size decreases
    {
        bool updateC = false;
        int n = conflictGraph[i].second.size();
        if(n != 0)
        {
            //if there are conflicting faces delete them
            std::vector<Edge> edges;
            std::vector<int> facesToRemove;
            for (int j = 0; j < n; j++)
            {
                int faceIdx = conflictGraph[i].second[j];
                Face f = faces[faceIdx];

                Edge e1 = {f.p1, f.p2, f};
                Edge e2 = {f.p2, f.p3, f};
                Edge e3 = {f.p3, f.p1, f};

                auto toggleEdge = [&](Edge e) {
                    if (e.a > e.b) std::swap(e.a, e.b);

                    auto it = std::find(edges.begin(), edges.end(), e);
                    if (it != edges.end()) {
                        edges.erase(it);
                    } else {
                        edges.push_back(e); 
                    }
                };

                toggleEdge(e1);
                toggleEdge(e2);
                toggleEdge(e3);

                facesToRemove.emplace_back(faceIdx);
            }

            std::sort(facesToRemove.begin(), facesToRemove.end(), std::greater<int>());
            for (std::vector<int>::iterator it = facesToRemove.begin(); it != facesToRemove.end(); ++it) {
                int faceIdx = *it;
                faces[faceIdx] = faces.back();
                faces.pop_back();
            }
            
            n = edges.size();
            for (int j = 0; j < n; j++)
            {
                int a = edges[j].a;
                int b = edges[j].b;
                int c = conflictGraph[i].first;

                Face oldFace = edges[j].oldFace;
                vector3 oldnormal = (verticies[oldFace.p2] - verticies[oldFace.p1]) * (verticies[oldFace.p3] - verticies[oldFace.p1]);
                Face f1 = {a, b, c};

                vector3 normal = (verticies[b] - verticies[a]) * (verticies[c] - verticies[a]);

                if (normal % oldnormal < 0) {
                    std::swap(f1.p2, f1.p3);
                }
                
                faces.push_back(f1);
            }
            updateC = true;
        }
        
        //remove from conflict graph
        conflictGraph[i] = conflictGraph.back();
        conflictGraph.pop_back(); 

        if(updateC)
        {
            n = conflictGraph.size();
            fcount = faces.size();
            for (int k = 0; k < n; k++)
            {
                conflictGraph[k].second.clear();
                for (int j = 0; j < fcount; j++)
                {
                    if(CanFaceSeePoint(verticies, faces[j], verticies[conflictGraph[k].first]))
                    {
                        conflictGraph[k].second.push_back(j);
                    }
                }
            }
        }
    }

    std::map<int, int> vertecesUsed;
    int n = faces.size();
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (vertecesUsed.emplace(faces[i].p1, counter).second)    
        {
            counter++;
        }
        if (vertecesUsed.emplace(faces[i].p2, counter).second)    
        {
            counter++;
        }
        if (vertecesUsed.emplace(faces[i].p3, counter).second)    
        {
            counter++;
        }
    }
    vertexSize = vertecesUsed.size()*3;
    int indexSize = faces.size()*3;
    int normalsSize = faces.size();    

    std::shared_ptr<solar::Mesh> mesh = std::make_shared<solar::Mesh>(name.length(), vertexSize, indexSize, normalsSize);

    n = vertecesUsed.size();
    std::map<int, int>::iterator it = vertecesUsed.begin();
    for (int i = 0; i < n; i++)
    {
        mesh->vertices[it->second*3+0] = verticies[it->first].x();
        mesh->vertices[it->second*3+1] = verticies[it->first].y();
        mesh->vertices[it->second*3+2] = verticies[it->first].z();
        it++;
    }
    
    n = indexSize/3;
    for (int i = 0; i < n; i++)
    {
        mesh->vertexIndices[i*3+0] = vertecesUsed[faces[i].p1];
        mesh->vertexIndices[i*3+1] = vertecesUsed[faces[i].p3];
        mesh->vertexIndices[i*3+2] = vertecesUsed[faces[i].p2];

        mesh->normalIndices[i*3+0] = i;
        mesh->normalIndices[i*3+1] = i;
        mesh->normalIndices[i*3+2] = i;
        mesh->textureIndices[i*3+0] = 0;
        mesh->textureIndices[i*3+1] = 0;
        mesh->textureIndices[i*3+2] = 0;

        vector3 normal;
        normal = (verticies[faces[i].p3] - verticies[faces[i].p1]) * (verticies[faces[i].p2] - verticies[faces[i].p1]);
        normal = normal.Normalized();
        mesh->normals[i*4+0] = normal.x();
        mesh->normals[i*4+1] = normal.y();
        mesh->normals[i*4+2] = normal.z();
        mesh->normals[i*4+3] = 0;//padding as requested by SSBO
    }
    
    for (int i = 0; i < name.length(); i++)
    {
        mesh->name[i] = name[i];
    }
    
    delete[] verticies;
    return mesh;
}

bool AreCoplanar(vector3 p1, vector3 p2, vector3 p3, vector3 p4)
{
    vector3 cross = (p3-p1) * (p2-p1);
    return std::abs(cross % (p4-p1)) < 0.000001;
}

bool CanFaceSeePoint(vector3* vertexes, Face f, vector3 p)
{
    vector3 cross = (vertexes[f.p3]-vertexes[f.p1]) * (vertexes[f.p2]-vertexes[f.p1]);
    vector3 toPoint = p - vertexes[f.p1];
    return toPoint % cross > 0.000001;
}
