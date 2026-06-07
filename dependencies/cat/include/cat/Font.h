#pragma once
#include <memory>

struct FT_Face; 
namespace cat
{
	
class Font
{
	std::unique_ptr<FT_Face> font;
};
}