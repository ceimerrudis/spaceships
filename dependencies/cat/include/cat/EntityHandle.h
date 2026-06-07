#pragma once 
#include "Entity.h"

namespace cat 
{
class Game;
struct EntityHandle {
    Entity entity = {};
    bool deleted = true;
	
	void Init(Game* game);
	
	~EntityHandle();
};
}
