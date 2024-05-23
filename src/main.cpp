#define SDL_MAIN_HANDLED
#include <iostream> 
#include <SDL2/SDL.h>

#include "Game.hpp"


int main() {
    printf("Hello, Matrix\n");

    Game game;
    if(game.Game_Init()){
        game.Game_RunLoop();
    }

    game.Game_Shutdown();
    return 0;
}