#pragma once
#include "cat/Game.h"
//#include "cat/dependencies/entt/entt.hpp"

namespace cat
{
class Entity
//WARNING MUST NOT CHANGE STRUCTURE REINTERPERATE CAST RELIES ON IT
{
friend struct EntityHandle;
private:
	
	void Init(Game* game);
	
public:
	entt::entity EnTT_id;//public so Game can destroy this entity
	
	template<typename T>
	T& GetComponent(Game* game) const
	{
		T* p = game->entt_registry->try_get<T>(EnTT_id);
		if(p == nullptr)
		{
			error("No such component");
		}
		return *p;
	}
	
	template<typename T>
	bool HasComponent(Game* game) const
	{
		return game->entt_registry->any_of<T>(EnTT_id);
	}


	template<typename T, typename... Args>
	T& AddComponent(Game* game, Args&&... args)
	{
		return game->entt_registry->emplace<T>(EnTT_id, std::forward<Args>(args)...);
	}

	template<typename T>
	void RemoveComponent(Game* game)
	{
		game->entt_registry->erase<T>(EnTT_id);
	}
	
	bool operator==(const Entity& other) const
	{
		return EnTT_id == other.EnTT_id;
	}
	
	bool operator!=(const Entity& other) const
	{
		return EnTT_id != other.EnTT_id;
	}
	
	Entity();//Init no data
	
	Entity(Game* game);
	
	~Entity();
};
}
