#pragma once
#include "cat/AdvancedMath.h"
#include "cat/Transform.h"

namespace cat
{
class CameraData
{
public:
    //Iegūst matricu lai pārietu  no pasaules koordinātēm uz novērotāja koordinātēm    
	Matrix<float, 4> projectionMatrix;
	
	//TODO pass params
	CameraData();
	
	void RecalculateProjectionMatrix(int width, int height, float size);
	
	Matrix<float, 4> WorldToObserverSpaceMatrix(Transform transform);
};
}
