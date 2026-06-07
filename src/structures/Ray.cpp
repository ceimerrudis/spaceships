#include "Ray.h"
#include "cat/cat.h"

Ray::Ray(cat::EntityHandle shooterEntity, cat::Vector<float, 3> origin, cat::Vector<float, 3> direction) :
shooterEntity(shooterEntity)
{
	this->origin = origin;
	this->direction = direction;
}