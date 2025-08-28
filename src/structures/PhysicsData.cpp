#include "PhysicsData.h"

void PhysicsData::AddVelocity(Vector<float, 3> direction, float amount)
{
    velocity = velocity + (direction * amount);
    if(velocity.Magnitude() > 10)
    {
        //velocity = velocity.Normalized() * 10;
    }
}
    
void PhysicsData::AddAngularVelocity(Vector<float, 3> axis, float amount)
{
    angularVelocity = angularVelocity + (axis * amount);
    if(angularVelocity.Magnitude() > 0.08)
    {
        angularVelocity = angularVelocity.Normalized() * 0.08;
    }
}