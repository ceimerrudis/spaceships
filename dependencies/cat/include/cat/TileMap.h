#pragma once
#include <vector>
#include <array>
#include <memory>
#include "cat/Game.h"
#include "cat/AdvancedMath.h"
#include "cat/Letter.h"
#include "cat/Renderable.h"

namespace cat 
{
struct Tile
{
	char id;
	std::shared_ptr<unsigned int> textureKey;
};
	 
struct TileMap
{
public:
	int width;
	int height;
	std::vector<Tile> tileSet;
	Vector<int, 2> tileSize;

	std::vector<char> tilemap;

	TileMap(int width, int height);

	void AddTileToSet(char id, std::shared_ptr<unsigned int> textureKey);

	void LoadMap(std::string mapString);

	void SetTile(cat::Vector<int, 2> position, char tile);

	void ClearTile(cat::Vector<int, 2> position);
	
	char& GetTile(cat::Vector<int, 2> position);
	
	Tile GetTileData(char tile);
	
	inline Tile GetTileData(cat::Vector<int, 2> position)
	{ return GetTileData(GetTile(position)); }
};
}