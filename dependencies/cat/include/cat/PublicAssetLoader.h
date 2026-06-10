#pragma once
#include <memory>
#include <filesystem>

namespace cat
{
class AssetLoader;
class TextureResource;
class Mesh;
class PublicAssetLoader
{
public:
	PublicAssetLoader();
	
	std::unique_ptr<AssetLoader> assetLoader;
	
	//unordered_map<uint64_t, AssetId>::iterator GetResourceIdIndex(const path& assetPath, AssetType assetType = AssetType::Unknown);

    //AssetId GetResourceID(const path& assetPath, AssetType assetType = AssetType::Unknown);

    uint64_t GetResourceID(uint64_t font_id, char32_t chr);

	uint64_t LoadObject(const std::string& fileName, bool flipWinding = false);

	uint64_t LoadImage(const std::string& fileName);

	uint64_t LoadFont(const std::string& fileName);
	
	std::shared_ptr<Mesh> GetMeshAsset(uint64_t assetId);
	
	TextureResource GetTextureAsset(uint64_t assetId);
	
	void DeleteAsset(uint64_t assetId);
	
	bool AssetExists(uint64_t assetId);
};
}