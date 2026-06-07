#include "cat/cat.h"
#include "SpaceshipGame.h"

using namespace cat;

void SpaceshipGame::InitKeybinds()
{
	cat::Input temp;
	temp.state = 0;

	//TEMPORARY
	temp.keyname = W;
    temp.keycode = KEY_W;
	inputSystem->AddKey(temp);
	temp.keyname = A;
    temp.keycode = KEY_A;
	inputSystem->AddKey(temp);
	temp.keyname = S;
    temp.keycode = KEY_S;
	inputSystem->AddKey(temp);
	temp.keyname = D;
    temp.keycode = KEY_D;
	inputSystem->AddKey(temp);
	
	//SHIP CONTROLLS
    temp.keyname = ROLL_CLOCKWISE_KEY;
    temp.keycode = KEY_SPACE;
	inputSystem->AddKey(temp);
	temp.keyname = ROLL_ANTI_CLOCKWISE_KEY;
    temp.keycode = KEY_Q;
	inputSystem->AddKey(temp);
	temp.keyname = BREAK_KEY;
	temp.keycode = KEY_Z;
	inputSystem->AddKey(temp);
	temp.keyname = MOVE_LEFT_KEY;
    temp.keycode = KEY_LEFT;
	inputSystem->AddKey(temp);
	temp.keyname = MOVE_FORWARD_KEY;
    temp.keycode = KEY_UP;
	inputSystem->AddKey(temp);
	temp.keyname = MOVE_RIGHT_KEY;
    temp.keycode = KEY_RIGHT;
	inputSystem->AddKey(temp);
	temp.keyname = YAW_LEFT_KEY;
    temp.keycode = KEY_NUM_LOCK;
	inputSystem->AddKey(temp);
	temp.keyname = YAW_RIGHT_KEY;
    temp.keycode = KEY_NUM_LOCK;
	inputSystem->AddKey(temp);
	temp.keyname = THROTTLE_DOWN_KEY;
    temp.keycode = KEY_X;
	inputSystem->AddKey(temp);
	temp.keyname = THROTTLE_UP_KEY;
    temp.keycode = KEY_C;
	inputSystem->AddKey(temp);
	temp.keyname = FIRE_KEY;
    temp.keycode = KEY_NUM_LOCK;
	inputSystem->AddKey(temp);
	
	//MISC
	temp.keyname = ESCAPE_KEY;
    temp.keycode = KEY_ESCAPE;
	inputSystem->AddKey(temp);
	temp.keyname = VIEWPOINT_CHANGE;
    temp.keycode = KEY_F5;
	inputSystem->AddKey(temp);
	temp.keyname = QUIT_GAME;
    temp.keycode = KEY_F10;
	inputSystem->AddKey(temp);
	
	temp.keyname = 20;
    temp.keycode = KEY_F11;
	inputSystem->AddKey(temp);
}