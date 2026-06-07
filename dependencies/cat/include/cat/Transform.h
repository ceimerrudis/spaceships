#pragma once
#include "cat/AdvancedMath.h"
#include "cat/Game.h"

namespace cat 
{
class Transform
{
public:
    Vector<float, 3> position;
    Vector<float, 3> right;
    Vector<float, 3> up;
    Vector<float, 3> forward;
    Matrix<float, 4> transformMatrix;
	
	Transform();
	
	void Move(float x, float y, float z);

	inline void Move(Vector<float, 3> translate){
		Move(translate.data[0], translate.data[1], translate.data[2]);
	}

	void Rotate(Vector<float, 3> axis, float angle);

	void UpdateTransformationMatrix();

	Vector<float, 3> rodriguesRotate(const Vector<float, 3>& v, const Vector<float, 3>& k, double theta);

	void Orthonormalize();

	void LookAt(Vector<float, 3> lookAt);
};
}
