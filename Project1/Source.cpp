#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "GameEngine.h"

#include "IntroState.h"
//#include "ExitState.h"
#include "LTexture.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//MyScene::Entity* myEntity;


void prepareScene(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void presentScene(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
}



int main(int argc, char *argv[]) {
    c_GameEngine game;
    game.Init("Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);

    bool quit = false;

    SDL_Event e;
	//MyScene myscene;
	

    //myscene.addBackgroundLayer(ltexture->loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\Layer_0001_8.png", renderer), 0, 0);
	//myscene.addBackgroundLayer(ltexture->loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\Layer_0000_9.png", renderer), 0, 0);
	//std::vector<MyScene::Entity> backgrounds = myscene.returnBackgrounds();

	//for (int i = 0; i < backgrounds.size(); i++) {
	//	myscene.createRect(backgrounds[i].x, backgrounds[i].y, SCREEN_WIDTH, SCREEN_HEIGHT);
	//	printf("%d, %d", backgrounds[i].x, backgrounds[i].y);
	//}

	//std::vector<SDL_Rect> rects = myscene.returnRects();
    //for (int i = 0; i < backgrounds.size(); i++) {
	//myscene.createRect(backgrounds[i].x, backgrounds[i].y, SCREEN_WIDTH, SCREEN_HEIGHT);
	//printf("%d, %d", backgrounds[i].x, backgrounds[i].y);
	//}

	//std::vector<SDL_Rect> rects = myscene.returnRects();
    game.ChangeState(c_IntroState::Instance());

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