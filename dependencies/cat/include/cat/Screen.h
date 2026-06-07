#pragma once

namespace cat 
{
struct Screen
{
	int width;//width in real pixels
	int height;//width in real pixels
	
	//int baseWidth;
	//int baseHeight;
	
	int pixelScaleWorld;
	int pixelScaleUI;
	
	//cached values calced from size and scale
	int pixelWidthWorld;
	int pixelHeightWorld;
	int pixelWidthUI;
	int pixelHeightUI;
	
	int xOverflowWorld;//how many physical pixels are left unrendered as they do not fit a multiple
	int yOverflowWorld;
	
	int xOverflowUI;
	int yOverflowUI;
	
	float pixelToNormalXWorld;//ndc amount of a single logical pixel
	float pixelToNormalYWorld;
	
	float pixelToNormalXUI;//ndc amount of a single logical pixel
	float pixelToNormalYUI;
};
}
