#include "Game.h"
/*
TODO 
CRITICAL:

HIGH:
fix asteroids

FEATURE:
ui
flight instruments
implement ai
implement ship textures 

POLISH:
HARD implement death animation
*/

int main()
{
    Logger::Init();
    {
        {
            Game game;
            while(game.Update()){}
        }//Destroy game and if that succeeds then 0
        glfwTerminate();//must terminate glfw after Game is destroyed a valid opengl context is nescasary for buffer deletion
    }
    LOG("close success");
    return 0;
}

