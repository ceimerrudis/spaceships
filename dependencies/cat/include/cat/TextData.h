#pragma once
#include <vector>
#include <memory>
#include "cat/Game.h"
#include "cat/AdvancedMath.h"
#include "cat/Letter.h"
#include "cat/Renderable.h"

namespace cat 
{
class GlyphCache;
class TextureManager;
struct TextData
{
public:
    Vector<float, 3> textDir;
    std::string text;
    int size;
	uint64_t fontAssetId;
    std::vector<Letter> letterTextureKeys;
    //std::shared_ptr<GlyphCache> glyphCache;//TODO is this needed?
	
	TextData(Renderable& renderable, uint64_t fontAssetId);
	
	void SetDirection(Vector<float, 3> direction);
};
}