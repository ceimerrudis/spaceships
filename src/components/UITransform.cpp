#include "UITransform.h"
#include "GLErrorHandling.h"
#include "Renderable.h"

void InitUITransform(UITransform& uiTransform)
{
    #if DEBUG
        uiTransform.initialized = true;
    #endif
    uiTransform.position = Vector<float, 2> {0, 0};
}

void SetPositionAndSize(UITransform& uiTransform, Renderable& renderable, Vector<float, 2> position, Vector<float, 2> size)
{
    uiTransform.position = position;
    uiTransform.size = size;
    uiTransform.anchor = UIAnchor::BottomLeft;

    std::array<float, 16> vertexes = {
        uiTransform.position.x(), uiTransform.position.y(), 0, 0,
        uiTransform.position.x(), uiTransform.position.y() + uiTransform.size.y(), 0, 1,
        uiTransform.position.x() + uiTransform.size.x(), uiTransform.position.y() + uiTransform.size.y(), 1, 1,
        uiTransform.position.x() + uiTransform.size.x(), uiTransform.position.y(), 1, 0
    };

    GL(glBindBuffer(GL_ARRAY_BUFFER, *renderable.vertexBufferKey));
    GL(glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(float), vertexes.data()));    
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
