#pragma once
#include <optional>
#include <string>
#include <cstdint>
#include "cat/AssetType.h"

namespace cat
{
struct AssetId
{
	std::string filePath;
	std::optional<uint32_t> index;
	AssetType type;
};
}
