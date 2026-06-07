#pragma once
#include "GlobalInclude.h"
#include "cat/cat.h"
#include <memory>

struct Collider
{
    unsigned int entityId;
    cat::Vector<float, 3> pos;
    float width;
    float height;
    float length;
    cat::Matrix<float, 3> rotation;
	
	Collider(
	cat::Vector<float, 3> position, 
	cat::Vector<float, 3> dimensions, 
	cat::Matrix<float, 3> rotation = cat::Matrix<float, 3>{
			1.0,0.0,0.0,
			0.0,1.0,0.0,
			0.0,0.0,1.0
		}
	);
};
