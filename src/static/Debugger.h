#pragma once
#include "GlobalInclude.h"
#include "Glyph.h"
#include "TextureResource.h"
#include "TextureManager.h"
#include "GlyphCache.h"
#include "DebugDraw.h"
#include <vector>
#include <memory>

class Debugger 
{
public:
    static std::vector<std::pair<DebugDraw, std::pair<Matrix<float, 4>*, Matrix<float, 4>*>>> debugs;

    inline static void Update()
    {
        int n = debugs.size();
        for (int i = 0; i < n; i++)
        { 
            debugs[i].first.Render(*debugs[i].second.first, *debugs[i].second.second);
        }
        
    }
};
