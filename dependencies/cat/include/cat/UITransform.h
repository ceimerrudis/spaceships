#pragma once
#include <array>
#include "cat/AdvancedMath.h"
#include "cat/Game.h"
#include "cat/Renderable.h"

namespace cat 
{


struct UITransform
{
public:
	Vector<float, 4> position;//relative x fixed x r y f y
	Vector<float, 4> size;
    std::array<float, 16> vertexes;
    std::array<unsigned int, 6> indicies;

	UITransform();

	//normalized x pixel x normalized y pixel y
	void SetPositionAndSizeWithAnchors(Game* game, Renderable& renderable, Vector<float, 4> position, Vector<float, 4> size);

	void RefreshPositionAndSize(Game* game, Renderable& renderable);
	
	//Gets the position in normalized screen space of the bottom left corner
	Vector<float, 2> GetPosition(Screen& screen);
	
	//Gets the full size in normalized screen space
	Vector<float, 2> GetSize(Screen& screen);
};
}
