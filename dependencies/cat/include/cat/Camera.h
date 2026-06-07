#pragma once
#include "cat/Logger.h"
#include "AdvancedMath.h"
#include "cat/Transform.h"
#include "Entity.h"
#include "cat/CameraData.h"

namespace cat 
{
class Game;

struct Camera 
{
public:
    Entity entity;
	
    Camera(Game* game);

    ~Camera();
};
}