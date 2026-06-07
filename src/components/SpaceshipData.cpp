#include "SpaceshipData.h"

SpaceshipData::SpaceshipData()
{
    health = 20;
    throttle = 0;
    isAlive = true;
    isPlayer = false;
    fireCooldown = 0;
    commandCooldown = 0;
    aiThrottle = 0;
    aiFire = 0;
    aiYaw = 0;
    aiRoll = 0;
    aiPitch = 0;
    aiMoveRight = 0;
    aiMoveForward = 0;
    physicsData.velocity = cat::Vector<float, 3>{0, 0, 0};
    physicsData.angularVelocity = cat::Vector<float, 3>{0, 0, 0};
}

void SpaceshipData::Update(const cat::InputSystem& inputSystem, cat::Game* game, std::shared_ptr<cat::EntityHandle> spacehipEntity)
{
	if(isPlayer)
    { 
        aiThrottle = 0;
        aiFire = 0;
        aiYaw = 0;
        aiRoll = 0;
        aiPitch = 0;
        aiMoveRight = 0;
        aiMoveForward = 0;
        aiBreaks = 0;
        
		if(inputSystem.IsKeyHeld(W)){ aiMoveForward += 1;}
		if(inputSystem.IsKeyHeld(D)){ aiMoveRight += 1;}
		if(inputSystem.IsKeyHeld(S)){ aiMoveForward -= 1;}
		if(inputSystem.IsKeyHeld(A)){ aiMoveRight -= 1;}
		
        //if(inputSystem.IsKeyHeld(BREAK_KEY)){ aiBreaks = 1;}
        
        //if(inputSystem.IsKeyHeld(FIRE_KEY)){ aiFire = 1;}

        if(inputSystem.IsKeyHeld(THROTTLE_UP_KEY)){ aiThrottle += 1;}
        if(inputSystem.IsKeyHeld(THROTTLE_DOWN_KEY)){ aiThrottle -= 1;}

        if(inputSystem.IsKeyHeld(ROLL_CLOCKWISE_KEY)){ aiRoll += 1;}
        if(inputSystem.IsKeyHeld(ROLL_ANTI_CLOCKWISE_KEY)){ aiRoll -= 1;}
        aiRoll *= 80;
        
        //if(inputSystem.IsKeyHeld(MOVE_RIGHT_KEY)){ aiMoveRight += 1;}
        //if(inputSystem.IsKeyHeld(MOVE_LEFT_KEY)){ aiMoveRight -= 1;}
        //if(inputSystem.IsKeyHeld(MOVE_FORWARD_KEY)){ aiMoveForward += 1;}

        inputSystem.GetMouseDelta(&aiYaw, &aiPitch);
        //aiYaw  = clamp(aiYaw, -80, 80);
        //aiPitch = clamp(aiPitch, -80, 80);
    }
    else{
        //ai
        throttle = 100;
        if(commandCooldown == 0)
        {
            //aiYaw = RandomF(-80, 80);
            //aiRoll = RandomI(-1, 1)*80;
            //aiPitch = RandomF(-80, 80);
            
            commandCooldown = COMMAND_COOLDOWN;
        }
        else
        {
            commandCooldown--;
        }
    }
    
    throttle += (aiThrottle);
    if(throttle > MAX_THROTTLE)
    {
        throttle = MAX_THROTTLE;
    }
    if(throttle < -MAX_THROTTLE)
    {
        throttle = -MAX_THROTTLE;
    }
	
	cat::Transform& transform = spacehipEntity->entity.GetComponent<cat::Transform>(game);
    cat::Vector<float, 3> thrustDir;
    if(aiBreaks == 1)
    {
        thrustDir = cat::Vector<float, 3> {0,0,0};
    }
    else
    {
        thrustDir = /*transform.forward*0.1f + */transform.right*aiMoveRight + transform.forward*aiMoveForward;
    }
    physicsData.AddVelocity(thrustDir.Normalized(), float(1000) / 80000);//10 throttle
    
    physicsData.AddAngularVelocity(transform.up, aiYaw / -1600);
    physicsData.AddAngularVelocity(transform.forward, aiRoll / 1600);
    physicsData.AddAngularVelocity(transform.right, aiPitch / 1600);
    
	//Rotate(up, aiYaw / -50);
    //Rotate(forward, aiRoll / 50);
    //Rotate(right, aiPitch / 50);
    
    physicsData.AddAngularVelocity(physicsData.angularVelocity.Normalized(), -0.001);
    
    if(aiBreaks > 0)
    {
        physicsData.AddVelocity(physicsData.velocity, -0.05);
    }else
    {
        physicsData.AddVelocity(physicsData.velocity, -0.01);
    }

    transform.Move(physicsData.velocity);
	transform.Move(cat::Vector<float, 3> {0.01,0,0});
    transform.Rotate(physicsData.angularVelocity.Normalized(), physicsData.angularVelocity.Magnitude());    
    //LookAt(transform, physicsData.velocity);


    if(fireCooldown == 0)
    {
        if(aiFire == 1){
            //Ray laserFire = Ray{
                //entity.ID,
                //cat::Vector<float, 3>{transform.position.x(), transform.position.y(), transform.position.z()},
                //cat::Vector<float, 3>{transform.forward.x(), transform.forward.y(), transform.forward.z()}
            //};
            //game->ShootLaser(laserFire);
            fireCooldown = FIRE_COOLDOWN;
        }
    }
    else
    {
        fireCooldown--;
    }
}
