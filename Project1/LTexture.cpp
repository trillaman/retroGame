
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"
#include "GameEngine.h"

SDL_Texture* LTexture::loadTexture(std::string path, SDL_Renderer* renderer)
{	
	c_GameEngine game = c_GameEngine();
	renderer = game.renderer;
	//renderer = c_GameEngine::Instance()->renderer;
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;
	loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		printf("Unable to load texture\n");
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture\n");
			printf("%s\n", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	SDL_SetSurfaceBlendMode(loadedSurface, SDL_BLENDMODE_BLEND);
	printf("Texture loaded");
	return newTexture;
}

void LTexture::addBackgroundLayer(SDL_Texture* texture, int posX, int posY) {
	printf("Adding background");
	Entity bg = { 0, 0, nullptr };
	memset(&bg, 0, sizeof(Entity));
	bg.x = posX;
	bg.y = posY;
	bg.texture = texture;
	backgrounds.push_back(bg);
}


void LTexture::createRect(int x, int y, int WIDTH, int HEIGHT) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = WIDTH;
	stretchRect.h = HEIGHT;
	backgroundRects.push_back(stretchRect);
}