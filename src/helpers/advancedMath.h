#pragma once
#include "GlobalInclude.h"
#include <math.h>
#include "Matrix.h"
#include "Vector.h"

Matrix<float, 4>  CreateProjectionMatrix(int width, int height, float size);
