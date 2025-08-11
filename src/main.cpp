#include "Game.h"
/*
TODO 
implement collider
implement raycast
implement update ship
*/

int main()
{
    Logger::Init();
    {
        {
            Game game;
            while(game.Update())
            {}
        }//Destroy game and if that succeeds then 0
        glfwTerminate();//must terminate glfw after Game is destroyed a valid opengl context is nescasary for buffer deletion
    }
    LOG("close success");
    return 0;
}

