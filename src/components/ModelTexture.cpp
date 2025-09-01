#include "ModelTexture.h"

void InitModelTexture(ModelTexture& modelTexture, std::shared_ptr<unsigned int> textureKey)
{
    modelTexture.textureKey = textureKey;
}
