#pragma once
#include "cat/AdvancedMath.h"
#include "cat/Game.h"

namespace cat 
{
class Transform2D
{
public:
    Vector<float, 2> position;
    
	Transform2D();
	
	void Move(float x, float y);

	inline void Move(Vector<float, 2> translate){
		Move(translate.data[0], translate.data[1]);
	}
};
}
