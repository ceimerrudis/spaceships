#pragma once
#include <ostream>

namespace cat 
{
enum class AssetType
{
	Unknown,
	Model,
	Texture,
	Font,
};

inline std::ostream& operator<<(std::ostream& os, AssetType type)
{
	switch(type)
	{
		case AssetType::Model:   return os << "Model";
		case AssetType::Texture: return os << "Texture";
		case AssetType::Font:   return os << "Font";
		default:                     return os << "Unknown";
	}
}
}