#include "SpaceshipGame.h"
#include "cat/cat.h"
#include <csignal>

int main()
{
	CAT_DEBUG_LOG_SOURCE_IN_FILE = true;
	cat::Logger::Init();
	{
		SpaceshipGame game;
		while(game.Update()){}
	}
#if DEBUG
	LOG("close success");
#endif
    return 0;
}

