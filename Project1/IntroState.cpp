#include "IntroState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
#include "LTexture.h"

c_IntroState c_IntroState::m_IntroState;
MyScene::Entity* myEntity;

LTexture ltextureIntro;


void c_IntroState::Init(c_GameEngine* game) {
	SDL_SetRenderDrawColor(game->renderer, 0xFF, 0x00, 0x00, 0xFF);

	ltextureIntro.addBackgroundLayer(ltextureIntro.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\Layer_0001_8.png", game->renderer), 0, 0);

	for (int i = 0; i < ltextureIntro.backgrounds.size(); i++) {
		ltextureIntro.createRect(ltextureIntro.backgroundRects[i].texture, ltextureIntro.backgrounds[i].x, ltextureIntro.backgrounds[i].y, game->screenWidth, game->screenHeight);
	}
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

}

void c_IntroState::Draw(c_GameEngine* game) {


	printf("Layers size: %d\n", ltextureIntro.backgrounds.size());
	printf("Rects size: %d\n", ltextureIntro.backgroundRects.size());

	//ltexture.backgroundRects = ltexture.returnRects();

	for (int i = 0; i < ltextureIntro.backgroundRects.size(); i++) {
		SDL_RenderCopy(game->renderer, ltextureIntro.backgrounds[i].texture, NULL, &ltextureIntro.backgroundRects[i].stretchRect);
	}
}