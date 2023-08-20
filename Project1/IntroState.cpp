#include "IntroState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
#include "LTexture.h"

c_IntroState c_IntroState::m_IntroState;
MyScene::Entity* myEntity;

LTexture ltexture;

void c_IntroState::Init() {

	//}
	//ltexture.addBackgroundLayer(ltexture.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\Layer_0001_8.png", gRenderer), 0, -6);
	
	

	//for (int i = 0; i < ltexture.backgrounds.size(); i++) {
	//	ltexture.createRect(ltexture.backgrounds[i].x, ltexture.backgrounds[i].y, game.screenWidth, game.screenHeight);
	//	printf("%d, %d", ltexture.backgrounds[i].x, ltexture.backgrounds[i].y);
	//}

	//ltexture.backgroundRects = ltexture.returnRects();

}

void c_IntroState::Cleanup() {
	printf("IntroState Cleanup\n");
}

void c_IntroState::Pause() {
	printf("IntroState Pause\n");
}

void c_IntroState::Resume() {
	printf("IntroState Resume\n");
}

void c_IntroState::HandleEvents(c_GameEngine* game) {
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN) {
			game->Quit();
		}
		
	}
}

void c_IntroState::Update(c_GameEngine* game) {
	//SDL_UpdateWindowSurface(game->window);
}

void c_IntroState::Draw(c_GameEngine* game) {
	
	//SDL_RenderClear(game->GetRenderer());
	//SDL_SetRenderDrawColor(game->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderPresent(game->GetRenderer());
	//ltexture.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\Layer_0000_9.png", gRenderer);
	//printf("Layer 0 loaded\n");
}