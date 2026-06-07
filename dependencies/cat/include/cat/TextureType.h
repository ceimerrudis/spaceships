#pragma once
#include <ostream>

namespace cat
{
enum class TextureType
{
	Texture2D,
	CubeMap,
};

inline std::ostream& operator<<(std::ostream& os, TextureType type)
{
	switch(type)
	{
		case TextureType::Texture2D: return os << "Texture2D";
		case TextureType::CubeMap:   return os << "CubeMap";
		default:                     return os << "Unknown";
	}
}
}