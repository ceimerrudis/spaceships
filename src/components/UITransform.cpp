#include "UITransform.h"

void InitUITransform(UITransform& uiTransform)
{
    #if DEBUG
        uiTransform.initialized = true;
    #endif
    uiTransform.position = Vector<float, 2> {0, 0};
}

void SetPosition(UITransform& uiTransform, Vector<float, 2> position)
{
    uiTransform.position = position;
    uiTransform.anchor = UIAnchor::BottomLeft;
}

void SetSize(UITransform& uiTransform, Vector<float, 2> size)
{
    uiTransform.size = size;
}
