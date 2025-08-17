#include "Game.h"
/*
TODO 
CRITICAL:

HIGH:

FEATURE:
flight instruments
asteroids
implement ai
implement ship textures 
implement pseudo randomness

POLISH:
HARD implement death animation
*/

int main()
{
    Logger::Init();
    Remotery* rmt;
    rmt_CreateGlobalInstance(&rmt);
    {
        {
            Game game;
            while(game.Update())
            {}
        }//Destroy game and if that succeeds then 0
        glfwTerminate();//must terminate glfw after Game is destroyed a valid opengl context is nescasary for buffer deletion
    }
    LOG("close success");
    rmt_DestroyGlobalInstance(rmt); 
    return 0;
}

