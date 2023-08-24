#include "MenuState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
#include "LTexture.h"
#include <SDL_ttf.h>
#include <string>

c_MenuState c_MenuState::m_MenuState;
//MyScene::Entity* myEntity;

LTexture ltextureMenu;

void c_MenuState::Init(c_GameEngine* game) {
	SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xFF);
	ltextureMenu.addBackgroundLayer(ltextureMenu.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\sky.png", game->renderer), 0, 0, false);
	ltextureMenu.addBackgroundLayer(ltextureMenu.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\far-clouds.png", game->renderer), 0, 0, true);
	ltextureMenu.addBackgroundLayer(ltextureMenu.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\far-mountains.png", game->renderer), 0, 0, false);
	ltextureMenu.addBackgroundLayer(ltextureMenu.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\near-clouds.png", game->renderer), 0, 0, true);
	ltextureMenu.addBackgroundLayer(ltextureMenu.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\mountains.png", game->renderer), 0, 0, false);
	ltextureMenu.addBackgroundLayer(ltextureMenu.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\trees.png", game->renderer), 0, 0, false);
	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);

	for (int i = 0; i < ltextureMenu.backgrounds.size(); i++) {
		if (ltextureMenu.backgrounds[i].repeat == true) {
			int textureWidth = ltextureMenu.getTextureWidthInPixels(ltextureMenu.backgrounds[i].texture).x;
			int widthProp = game->screenWidth / textureWidth;
			printf("\nWidthProp: %d\n", widthProp);
			int posX = 0;
			for (int j = 0; j <= widthProp / 2; j++) {
				ltextureMenu.createRect(ltextureMenu.backgrounds[i].texture, ltextureMenu.backgrounds[i].x + posX, ltextureMenu.backgrounds[i].y, textureWidth * 2, game->screenHeight);
				posX += textureWidth * 2;
			}
		}
		else {
			ltextureMenu.createRect(ltextureMenu.backgrounds[i].texture, ltextureMenu.backgrounds[i].x, ltextureMenu.backgrounds[i].y, game->screenWidth, game->screenHeight);
		}
	}

	SDL_Color color = { 0, 0, 255 };
	std::string text = "BLAABLAAA";
	if (!ltextureMenu.loadText(text, color, game->renderer)) {
		printf("Failed to render text texture!\n");
	}
	

}

void c_MenuState::Cleanup() {
	printf("IntroState Cleanup\n");
}

void c_MenuState::Pause() {
	printf("IntroState Pause\n");
}

void c_MenuState::Resume() {
	printf("IntroState Resume\n");
}

void c_MenuState::HandleEvents(c_GameEngine* game) {
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN) {
			game->Quit();
		}

	}
}

void c_MenuState::Update(c_GameEngine* game) {

}

void c_MenuState::Draw(c_GameEngine* game) {


	printf("Layers size: %d\n", ltextureMenu.backgrounds.size());
	printf("Rects size: %d\n", ltextureMenu.backgroundRects.size());

	
	for (int i = 0; i < ltextureMenu.backgroundRects.size(); i++) {
		SDL_RenderCopy(game->renderer, ltextureMenu.backgroundRects[i].texture, NULL, &ltextureMenu.backgroundRects[i].stretchRect);
	}
	///SDL_RenderPresent(game->renderer);
}