#include "AsteroidGenerator.h"

using namespace cat::Random;

std::shared_ptr<cat::Mesh> GenAsteroid(unsigned int seed)
{
    std::string name = "Rand_asteroid_" + std::to_string(seed);
    SetRandomSeed(seed);
	
    int vertexSize = RandomI(20, 200);
	vertexSize = 172;
	vertexSize = 50;
	vertexSize = 5;
    Vector<float, 3>* verticies = new Vector<float, 3>[vertexSize];
	
	for(int i = 0; i < vertexSize; i++)
	{
		verticies[i].x() = RandomF(-10, 10);
		verticies[i].y() = RandomF(-10, 10);
		verticies[i].z() = RandomF(-10, 10);
	}

	int p = 0;
	verticies[p++] = { 1.799999, 8.581999, 5.456000};
	verticies[p++] = { 2.092000, -5.824000, -2.000000};
	verticies[p++] = { 4.748000, -8.900000, 8.408001};
	verticies[p++] = { 2.354000, -4.816000, 1.890000};
	verticies[p++] = { -1.318000, 6.576000, 2.258000};
    std::vector<Face> faces;
	
	ConvexHullGenerator(verticies, vertexSize, faces);
	//ConvexHullGeneratorV2(verticies, vertexSize, faces);

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

	std::shared_ptr<cat::Mesh> asteroidMesh = std::make_shared<cat::Mesh>(name.length(), vertexSize, indexSize, normalsSize);

    n = vertecesUsed.size();
    std::map<int, int>::iterator it = vertecesUsed.begin();
    for (int i = 0; i < n; i++)
    {
        asteroidMesh->vertices[it->second*3+0] = verticies[it->first].x();
        asteroidMesh->vertices[it->second*3+1] = verticies[it->first].y();
        asteroidMesh->vertices[it->second*3+2] = verticies[it->first].z();
        it++;
    }
    
    n = indexSize/3;
    for (int i = 0; i < n; i++)
    {
        asteroidMesh->vertexIndices[i*3+0] = vertecesUsed[faces[i].p1];
        asteroidMesh->vertexIndices[i*3+1] = vertecesUsed[faces[i].p2];
        asteroidMesh->vertexIndices[i*3+2] = vertecesUsed[faces[i].p3];

        asteroidMesh->normalIndices[i*3+0] = i;
        asteroidMesh->normalIndices[i*3+1] = i;
        asteroidMesh->normalIndices[i*3+2] = i;
		
        asteroidMesh->textureIndices[i*3+0] = 0;
        asteroidMesh->textureIndices[i*3+1] = 0;
        asteroidMesh->textureIndices[i*3+2] = 0;

        Vector<float, 3> normal;
        normal = (verticies[faces[i].p3] - verticies[faces[i].p1]) * (verticies[faces[i].p2] - verticies[faces[i].p1]);
        normal = normal.Normalized();
        asteroidMesh->normals[i*4+0] = normal.x();
        asteroidMesh->normals[i*4+1] = normal.y();
        asteroidMesh->normals[i*4+2] = normal.z();
        asteroidMesh->normals[i*4+3] = 0;//padding as requested by SSBO
    }
    
    for (int i = 0; i < name.length(); i++)
    {
        asteroidMesh->name[i] = name[i];
    }
    
    delete[] verticies;
    
	return asteroidMesh;
}

bool AreCoplanar(Vector<float, 3> p1, Vector<float, 3> p2, Vector<float, 3> p3, Vector<float, 3> p4)
{
    Vector<float, 3> cross = (p3-p1) * (p2-p1);
    return std::abs(cross % (p4-p1)) < 0.000001;
}

bool CanFaceSeePoint(Vector<float, 3>* vertexes, Face f, Vector<float, 3> p)
{
    Vector<float, 3> cross = (vertexes[f.p2]-vertexes[f.p1]) * (vertexes[f.p3]-vertexes[f.p1]);
    Vector<float, 3> toPoint = p - vertexes[f.p1];
    return toPoint % cross > 0.000001;
}

void ConvexHullGenerator(Vector<float, 3>* vertices, size_t vertexSize, std::vector<Face>& faces)
{
	std::vector<std::pair<int, std::vector<int>>> conflictGraph;

    int A = 0, B = 1, C = 2, D;
    Vector<float, 3> normal = (vertices[B] - vertices[A]) * (vertices[C] - vertices[A]);;
	while(C < vertexSize && normal.x() == 0.0 && normal.y() == 0.0 && normal.z() == 0.0)
	{
		C++;
		normal = (vertices[B] - vertices[A]) * (vertices[C] - vertices[A]);
	}
	if(C >= vertexSize)
	{
		error("ALL points of Generated asteroid are colinear. Sucks to be you.");
	}
	D = C + 1;
    while(D < vertexSize && AreCoplanar(vertices[0], vertices[1], vertices[2], vertices[D])){D++;}
    
	if(D >= vertexSize)
	{
		error("ALL points of Generated asteroid are coplanar. Sucks to be you.");
	}

	Face face = {A, B, C};
    if(CanFaceSeePoint(vertices, face, vertices[D]))
    {
        int s = C;
        C = B;
        B = s;
    }
	
	faces.push_back({A, B, C});
    faces.push_back({A, C, D});
    faces.push_back({C, B, D});
    faces.push_back({B, A, D});

    int fcount = faces.size();
    for (int i = 2; i < vertexSize; i++)//For each point left
    {
        if(i == A || i == B || i == C || i == D)
        {
            continue;
        }
        for (int j = 0; j < fcount; j++)// Go through each face and find conflicts
        {
            if(!CanFaceSeePoint(vertices, faces[j], vertices[i]))
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
                int c = conflictGraph[i].first;//vertex

                Face oldFace = edges[j].oldFace;
                Vector<float, 3> oldnormal = (vertices[oldFace.p2] - vertices[oldFace.p1]) * (vertices[oldFace.p3] - vertices[oldFace.p1]);
                Face f1 = {a, b, c};

                Vector<float, 3> normal = (vertices[b] - vertices[a]) * (vertices[c] - vertices[a]);

                if (normal % oldnormal > 0) {
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
                    if(!CanFaceSeePoint(vertices, faces[j], vertices[conflictGraph[k].first]))
                    {
                        conflictGraph[k].second.push_back(j);
                    }
                }
            }
        }
    }
}

//cube with correct winding
/*std::vector<Vector<float, 3>> vrt = {
		Vector<float, 3> {-1.0, -1.0, -1.0},
		Vector<float, 3> { 1.0, -1.0, -1.0},
		Vector<float, 3> { 1.0,  1.0, -1.0},
		Vector<float, 3> {-1.0,  1.0, -1.0},
		Vector<float, 3> {-1.0, -1.0,  1.0},
		Vector<float, 3> { 1.0, -1.0,  1.0},
		Vector<float, 3> { 1.0,  1.0,  1.0},
		Vector<float, 3> {-1.0,  1.0,  1.0}};
	
    for (int i = 0; i < vertexSize; i++)
    {
		verticies[i] = vrt[i];
        //verticies[i] = {RandomF(-20, 20), RandomF(-20, 20), RandomF(-20, 20)};
    }
    
    
	
	faces.push_back({0, 1, 2});
	faces.push_back({0, 2, 3});
	                     
	faces.push_back({4, 6, 5});
	faces.push_back({4, 7, 6});
	                     
	faces.push_back({4, 3, 7});
	faces.push_back({3, 4, 0});
	                     
	faces.push_back({1, 6, 2});
	faces.push_back({1, 5, 6});
	                     
	faces.push_back({2, 6, 3});
	faces.push_back({6, 7, 3});
	                     
	faces.push_back({0, 5, 1});
	faces.push_back({5, 0, 4});*/
	