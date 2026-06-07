#include "Collider.h"
#include "cat/cat.h"

Collider::Collider(cat::Vector<float, 3> position, cat::Vector<float, 3> dimensions, cat::Matrix<float, 3> rotation)
{
    pos = position;
    width = dimensions.x();
    height = dimensions.y();
    length = dimensions.z();
    this->rotation = rotation;
}