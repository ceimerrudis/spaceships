#pragma once
#include <math.h>
#include "cat/Matrix.h"
#include "cat/Vector.h"

namespace cat
{
Matrix<float, 4>  CreateProjectionMatrix(int width, int height, float size);

float clamp(float value, float min, float max);
}
