#include "IntroState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
#include "LTexture.h"
#include "ChoosePlayer.h"
#include <SDL_thread.h>
#include "Character.h"
#include <vector>

c_ChoosePlayer c_ChoosePlayer::m_ChoosePlayer;

LTexture ltexturePlayer;

Character* bawlerGirl;
Character* monk;

SDL_Color alphaColor = { 0, 0, 0, 150 };

int w = 0, h = 0, w2 = 0, h2 = 0;

int chosenPlayer = 0;
int activeButton = 0;

SDL_Thread* thread;

c_ChoosePlayer* inst = c_ChoosePlayer::Instance();

//This method is used to increase the frame of all characters in order to play idle animation
int increaseCharacterFrame(void* data) {
	while (true) {
		for (int i = 0; i < inst->characters.size(); i++) {
			inst->characters[i]->IncreaseCurrentFrame();
		}
	}
	return 0;
}

void c_ChoosePlayer::Init(c_GameEngine* game) {
	//INIT SCENE
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

	//Header text
	std::string chPlayer = "Choose Player";
	int chPlayerWidth = chPlayer.length() * 20;
	ltexturePlayer.createText({ game->screenWidth / 2 - (chPlayerWidth/2), 100, chPlayerWidth, 100 }, chPlayer, { 255, 255, 255, 255 }, {0,0}, game->renderer);

	//END OF INIT SCENE
	

	//Init character 1
	bawlerGirl = new Character("Bawler Girl", game->screenWidth / 2 - 550, 250);
	bawlerGirl->InitCharacter();

	//Load Idle animation
	if (bawlerGirl->InitIdleAnimation(game, "C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Players\\Brawler Girl\\idle.gif") != 1) {
		bawlerGirl->setWidth(bawlerGirl->idleAnim->w * 2);
		bawlerGirl->setHeight(bawlerGirl->idleAnim->h * 2);
	}

	//Init Chracter Rect
	bawlerGirl->InitCharacterRect();
	SDL_Rect rect = bawlerGirl->getRect();
	ltexturePlayer.playersRect.push_back(rect);

	inst->characters.push_back(bawlerGirl);

	//Create character button
	ltexturePlayer.createButton({ game->screenWidth / 2 - 400, 300, bawlerGirl->getNameWidth(), 100}, bawlerGirl->getName(), "CHOOSE", {0, 0, 255}, {0,0}, true, 0, 1, game->renderer);
	ltexturePlayer.modifyButton(activeButton, true, game->activeColor, ltexturePlayer.activeButton, game->renderer); // run this only once for first button

	//end of character 1



	//Init character 2

	monk = new Character("Monk", game->screenWidth / 2 - 500, 450);
	monk->InitCharacter();

	//Load Idle animation
	if (monk->InitIdleAnimation(game, "C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Players\\Monk\\01_idle_2.gif") != 1) {
		monk->setWidth(monk->idleAnim->w);
		monk->setHeight(monk->idleAnim->h);
	}

	//Init Chracter Rect
	monk->InitCharacterRect();
	SDL_Rect monkRect = monk->getRect();
	ltexturePlayer.playersRect.push_back(monkRect);

	inst->characters.push_back(monk);

	//Create character button
	ltexturePlayer.createButton({ game->screenWidth / 2 - 400, 450, monk->getNameWidth(), 100 }, monk->getName(), "CHOOSE", { 0, 0, 255 }, { 0,0 }, true, 1, 2, game->renderer);

	//end of character 2

	
	thread = SDL_CreateThread(increaseCharacterFrame, "func", NULL);

	if (thread == NULL) {
		printf("Couldnt create thread\n");
	}

	
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
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				printf("Pressing down\n");
				int actButton = ltexturePlayer.getActiveButton();
				if (actButton < ltexturePlayer.buttons.size() - 1) {
					ltexturePlayer.modifyButton(actButton, false, game->inactiveColor, ltexturePlayer.activeButton, game->renderer);
					ltexturePlayer.modifyButton(actButton + 1, true, game->activeColor, ltexturePlayer.activeButton, game->renderer);
					ltexturePlayer.setActiveButton(actButton + 1);
				}
				printf("Current active Button: %d\n", ltexturePlayer.getActiveButton());

			}
			if (event.key.keysym.sym == SDLK_UP) {
				printf("Pressing up\n");
				int actButton = ltexturePlayer.getActiveButton();
				if (actButton > 0) {
					ltexturePlayer.modifyButton(actButton, false, game->inactiveColor, ltexturePlayer.activeButton, game->renderer);
					ltexturePlayer.modifyButton(actButton - 1, true, game->activeColor, ltexturePlayer.activeButton, game->renderer);
					ltexturePlayer.setActiveButton(actButton - 1);
				}
				printf("Current active Button: %d\n", ltexturePlayer.getActiveButton());
			}
			
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

	SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(game->renderer, alphaColor.r, alphaColor.g, alphaColor.b, alphaColor.a);
	SDL_RenderFillRect(game->renderer, &ltexturePlayer.alphaRects[0].alpharect);

	for (int i = 0; i < ltexturePlayer.texts.size(); i++) {
		SDL_RenderCopy(game->renderer, ltexturePlayer.texts[i].texture, NULL, &ltexturePlayer.texts[i].rect);
	}

	for (int i = 0; i < ltexturePlayer.buttons.size(); i++) {
		SDL_RenderCopy(game->renderer, ltexturePlayer.buttons[i].texture, NULL, &ltexturePlayer.buttons[i].rect);
	}


	for (int i = 0; i < characters.size(); i++) {
		//characters[i]->PlayIdleAnimation2(game->renderer, &ltexturePlayer.playersRect[i]);

		SDL_RenderCopy(game->renderer, characters[i]->PlayIdleAnimation(), NULL, &ltexturePlayer.playersRect[i]);
	}
}
	

void c_ChoosePlayer::Close(c_GameEngine* game) {
	IMG_FreeAnimation(bawlerGirl->idleAnim);
	IMG_FreeAnimation(monk->idleAnim);
	for (int i = 0; i < characters.size(); i++) {
		SDL_free(characters[i]->idleAnimTextures);
		delete characters[i];
	}
	delete bawlerGirl;
	delete monk;
	SDL_WaitThread(thread, NULL);
	//SDL_WaitThread(thread2, NULL);
}

