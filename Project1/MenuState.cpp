#include "MenuState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
#include "LTexture.h"
#include <SDL_ttf.h>
#include <string>
#include "ChoosePlayer.h"
#include <SDL_mixer.h>

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
	
	ltextureMenu.createButton({ game->screenWidth / 2 - 200, game->screenHeight - 250, 100, 100 }, "PLAY", "PLAY", { 0, 0, 255 }, { game->screenWidth / 2 - 200, game->screenHeight - 250 }, true, 0, 1, game->renderer);
	ltextureMenu.createButton({game->screenWidth / 2 - 200, game->screenHeight - 100, 100, 100 }, "QUIT", "QUIT", { 0, 0, 255 }, { game->screenWidth / 2 - 200, game->screenHeight - 100 }, false, 1, 0 , game->renderer);


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

	ltextureMenu.activeButton = 0;
	ltextureMenu.modifyButton(activeButton, true, game->activeColor, ltextureMenu.activeButton, game->renderer);

	game->PlayMusic("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Music\\Billy's Sacrifice.mp3");
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
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				printf("Pressing down\n");
				int actButton = ltextureMenu.getActiveButton();
				if (actButton < ltextureMenu.buttons.size() - 1) {
					ltextureMenu.modifyButton(actButton, false, game->inactiveColor, ltextureMenu.activeButton, game->renderer);
					ltextureMenu.modifyButton(actButton + 1, true, game->activeColor, ltextureMenu.activeButton, game->renderer);
					ltextureMenu.setActiveButton(actButton + 1);
				}
				printf("Current active Button: %d\n", ltextureMenu.getActiveButton());

			}
			if (event.key.keysym.sym == SDLK_UP) {
				printf("Pressing up\n");
				int actButton = ltextureMenu.getActiveButton();
				if (actButton > 0) {
					ltextureMenu.modifyButton(actButton, false, game->inactiveColor, ltextureMenu.activeButton, game->renderer);
					ltextureMenu.modifyButton(actButton - 1, true, game->activeColor, ltextureMenu.activeButton, game->renderer);
					ltextureMenu.setActiveButton(actButton - 1);
				}
				printf("Current active Button: %d\n", ltextureMenu.getActiveButton());
			}
			if (event.key.keysym.sym == SDLK_RETURN) {
				printf("Pressing enter\n");
				if (ltextureMenu.getActiveButton() == 0) {
					this->Close(game);
					game->ChangeState(c_ChoosePlayer::Instance());
				}
				else if (ltextureMenu.getActiveButton() == 1) {
					this->Close(game);
					game->Quit();
				}
			}
		}
	}
}

void c_MenuState::Update(c_GameEngine* game) {

}

void c_MenuState::Draw(c_GameEngine* game) {
	
	for (int i = 0; i < ltextureMenu.backgroundRects.size(); i++) {
		SDL_RenderCopy(game->renderer, ltextureMenu.backgroundRects[i].texture, NULL, &ltextureMenu.backgroundRects[i].stretchRect);
	}

	for (int i = 0; i < ltextureMenu.buttons.size(); i++) {
		SDL_RenderCopy(game->renderer, ltextureMenu.buttons[i].texture, NULL, &ltextureMenu.buttons[i].rect);
	}

}

void c_MenuState::Close(c_GameEngine* game) {
	SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xFF);
	printf("IntroState Cleanup\n");
	//Mix_FreeMusic(game->gMusic);
	//game->gMusic = NULL;
	
	for (int i = 0; i < ltextureMenu.backgroundRects.size(); i++) {
		SDL_DestroyTexture(ltextureMenu.backgroundRects[i].texture);
	}

	for (int i = 0; i < ltextureMenu.buttons.size(); i++) {
		SDL_DestroyTexture(ltextureMenu.buttons[i].texture);
	}
}