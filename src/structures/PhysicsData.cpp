#include "PhysicsData.h"

void PhysicsData::AddVelocity(vector3 direction, float amount)
{
    velocity = velocity + (direction * amount);
    if(velocity.magnitude() > 10)
    {
        //velocity = velocity.Normalized() * 10;
    }
}
    
void PhysicsData::AddAngularVelocity(vector3 axis, float amount)
{
    angularVelocity = angularVelocity + (axis * amount);
    if(angularVelocity.magnitude() > 0.08)
    {
        angularVelocity = angularVelocity.Normalized() * 0.08;
    }
}