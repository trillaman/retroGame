#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "GameEngine.h"
#include "IntroState.h"

//#include "LTexture.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



int main(int argc, char *argv[]) {
    c_GameEngine game;
    game.Init("Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    game.screenWidth = SCREEN_WIDTH;
    game.screenHeight = SCREEN_HEIGHT;

    bool quit = false;

    SDL_Event e;
	
    game.ChangeState(c_IntroState::Instance());
    
    SDL_SetRenderDrawColor(game.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    while(game.Running()){

		game.HandleEvents();
		game.Update();
        game.Draw();

        SDL_RenderClear(game.renderer);
        SDL_RenderPresent(game.renderer);
		SDL_Delay(20);
    }

    game.Cleanup();

    return 0;
}