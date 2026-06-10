#pragma once	
#include "cat/cat.h"

using cat::Vector;

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

std::shared_ptr<cat::Mesh> GenAsteroid(unsigned int seed);
	
bool AreCoplanar(Vector<float, 3> p1, Vector<float, 3> p2, Vector<float, 3> p3, Vector<float, 3> p4);

bool CanFaceSeePoint(Vector<float, 3>* vertexes, Face f, Vector<float, 3> p);

bool CanFaceSeePoint(cat::Vector<float, 3> p1, cat::Vector<float, 3> p2, cat::Vector<float, 3> p3, cat::Vector<float, 3> pointToCheck);

void ConvexHullGeneratorV2(Vector<float, 3>* vertices, size_t vertexSize, std::vector<Face>& faces);

void ConvexHullGenerator(Vector<float, 3>* vertices, size_t vertexSize, std::vector<Face>& faces);
