#pragma once
#include "GlobalInclude.h"
#include "cat/cat.h"
#include <memory>

struct Ray {
    cat::EntityHandle shooterEntity;
    cat::Vector<float, 3> origin;
    cat::Vector<float, 3> direction;
	
	Ray(cat::EntityHandle shooterEntity, cat::Vector<float, 3> origin, cat::Vector<float, 3> direction);
};