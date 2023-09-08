#include "IntroState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
#include "LTexture.h"
#include "ChoosePlayer.h"

c_ChoosePlayer c_ChoosePlayer::m_ChoosePlayer;


LTexture ltexturePlayer;

SDL_Color alphaColor = { 0, 0, 0, 150 };
IMG_Animation* anim;
int w, h;
int current_frame, delay;
SDL_Texture** textures;

int chosenPlayer = 0;
int activeButton = 0;





void c_ChoosePlayer::Init(c_GameEngine* game) {
	SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xAA);
	ltexturePlayer.addBackgroundLayer(ltexturePlayer.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\sky.png", game->renderer), 0, 0, false);
	ltexturePlayer.addBackgroundLayer(ltexturePlayer.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\far-clouds.png", game->renderer), 0, 0, true);
	ltexturePlayer.addBackgroundLayer(ltexturePlayer.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\far-mountains.png", game->renderer), 0, 0, false);
	ltexturePlayer.addBackgroundLayer(ltexturePlayer.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\near-clouds.png", game->renderer), 0, 0, true);
	ltexturePlayer.addBackgroundLayer(ltexturePlayer.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\mountains.png", game->renderer), 0, 0, false);
	ltexturePlayer.addBackgroundLayer(ltexturePlayer.loadTexture("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\BG\\MenuState\\trees.png", game->renderer), 0, 0, false);

	
	for (int i = 0; i < ltexturePlayer.backgrounds.size(); i++) {
		if (ltexturePlayer.backgrounds[i].repeat == true) {
			int textureWidth = ltexturePlayer.getTextureWidthInPixels(ltexturePlayer.backgrounds[i].texture).x;
			int widthProp = game->screenWidth / textureWidth;
			printf("\nWidthProp: %d\n", widthProp);
			int posX = 0;
			for (int j = 0; j <= widthProp / 2; j++) {
				ltexturePlayer.createRect(ltexturePlayer.backgrounds[i].texture, ltexturePlayer.backgrounds[i].x + posX, ltexturePlayer.backgrounds[i].y, textureWidth * 2, game->screenHeight);
				posX += textureWidth * 2;
			}
		}
		else {
			ltexturePlayer.createRect(ltexturePlayer.backgrounds[i].texture, ltexturePlayer.backgrounds[i].x, ltexturePlayer.backgrounds[i].y, game->screenWidth, game->screenHeight);
		}
	}

	//Alpha to dim the background
	ltexturePlayer.createRectWithColor(alphaColor, 0, 0, game->screenWidth, game->screenHeight);


	std::string chPlayer = "Choose Player";
	int chPlayerWidth = chPlayer.length() * 20;
	ltexturePlayer.createText({ game->screenWidth / 2 - (chPlayerWidth/2), 100, chPlayerWidth, 100 }, chPlayer, { 255, 255, 255, 255 }, {0,0}, game->renderer);

	std::string player1 = "Bawler Girl";
	int chBowlerWidth = player1.length() * 20;

	ltexturePlayer.createButton({ game->screenWidth / 2 - 400, 300, chPlayerWidth, 100 }, player1, "CHOOSE", {0, 0, 255}, {0,0}, true, 0, 1, game->renderer);
	ltexturePlayer.modifyButton(activeButton, true, game->activeColor, ltexturePlayer.activeButton, game->renderer);
	//ltexturePlayer.createText({ game->screenWidth / 2 - 400, 300, chPlayerWidth, 100}, player1, { 255, 255, 255, 255 }, { 0,0 }, game->renderer);

	anim = IMG_LoadAnimation("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Players\\Brawler Girl\\idle.gif");
	
	if (!anim) {
		printf("Cannot load animation\n");
	}
	w = anim->w * 2;
	h = anim->h * 2;

	textures = (SDL_Texture**)SDL_calloc(anim->count, sizeof(*textures));

	if (!textures) {
		IMG_FreeAnimation(anim);
	}

	for (int j = 0; j < anim->count; ++j) {
	 	textures[j] = SDL_CreateTextureFromSurface(game->renderer, anim->frames[j]);
	}

	current_frame = 0;

	SDL_Rect playerRect;
	playerRect.x = game->screenWidth / 2 - 550;
	playerRect.y = 250;
	playerRect.w = w;
	playerRect.h = h;

	ltexturePlayer.playersRect.push_back(playerRect);

	
}

void c_ChoosePlayer::Cleanup() {
	printf("Choose Player Cleanup\n");
}

void c_ChoosePlayer::Pause() {
	printf("Choose Player Pause\n");
}

void c_ChoosePlayer::Resume() {
	printf("Choose Player Resume\n");
}

void c_ChoosePlayer::HandleEvents(c_GameEngine* game) {
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN) {
			game->Quit();
		}

	}
}

void c_ChoosePlayer::Update(c_GameEngine* game) {
}

void c_ChoosePlayer::Draw(c_GameEngine* game) {
	for (int i = 0; i < ltexturePlayer.backgroundRects.size(); i++) {
		SDL_RenderCopy(game->renderer, ltexturePlayer.backgroundRects[i].texture, NULL, &ltexturePlayer.backgroundRects[i].stretchRect);
	}

	for (int i = 0; i < ltexturePlayer.alphaRects.size(); i++) {
		SDL_RenderCopy(game->renderer, NULL, NULL, &ltexturePlayer.alphaRects[i].alpharect);
	}
	//SDL_GetRenderDrawBlendMode(game->renderer, &ltexturePlayer.blendMode);
	SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(game->renderer, alphaColor.r, alphaColor.g, alphaColor.b, alphaColor.a);
	SDL_RenderFillRect(game->renderer, &ltexturePlayer.alphaRects[0].alpharect);

	for (int i = 0; i < ltexturePlayer.texts.size(); i++) {
		SDL_RenderCopy(game->renderer, ltexturePlayer.texts[i].texture, NULL, &ltexturePlayer.texts[i].rect);
	}

	if (anim->delays[current_frame]) {
		delay = anim->delays[current_frame];
	}
	SDL_Delay(delay);

	current_frame = (current_frame + 1) % anim->count;
	
	for (int i = 0; i < ltexturePlayer.buttons.size(); i++) {
		SDL_RenderCopy(game->renderer, ltexturePlayer.buttons[i].texture, NULL, &ltexturePlayer.buttons[i].rect);
	}
	

	SDL_RenderCopy(game->renderer, textures[current_frame], NULL, &ltexturePlayer.playersRect[0]);

	//ltexture.backgroundRects = ltexture.returnRects();

}