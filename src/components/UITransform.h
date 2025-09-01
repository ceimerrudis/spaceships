#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include <array>
#include "Renderable.h"

enum class UISpaceMode 
{
    Relative,
    Fixed
};

enum class UIAnchor 
{
    TopLeft,
    TopCenter,
    TopRight,
    MiddleLeft,
    Center,
    MiddleRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

struct UITransform
{
    #if DEBUG
        bool initialized;
    #endif
    UIAnchor anchor;
    UISpaceMode mode;
    Vector<float, 2> position;
    Vector<float, 2> size;
    std::array<float, 16> vertexes;
    std::array<unsigned int, 6> indicies;
};

void InitUITransform(UITransform& uiTransform);

void SetPositionAndSize(UITransform& uiTransform, Renderable& renderable, Vector<float, 2> position, Vector<float, 2> size);
