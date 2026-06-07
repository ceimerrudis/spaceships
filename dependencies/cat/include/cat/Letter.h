#pragma once
#include "cat/AdvancedMath.h"
#include <memory>

namespace cat{
struct Letter
{
    int offset;
    Vector<int, 2> size;
    std::shared_ptr<unsigned int> textureKey;
	Vector<int, 2> bearing;
};
}
