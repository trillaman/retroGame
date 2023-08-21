
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"
#include "GameEngine.h"

SDL_Texture* LTexture::loadTexture(std::string path, SDL_Renderer* renderer)
{	
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
	bg.repeat = false;
	backgrounds.push_back(bg);
}

void LTexture::addBackgroundLayer(SDL_Texture* texture, int posX, int posY, bool repeat) {
	printf("Adding background");
	Entity bg = { 0, 0, nullptr };
	memset(&bg, 0, sizeof(Entity));
	bg.x = posX;
	bg.y = posY;
	bg.texture = texture;
	bg.repeat = repeat;
	
	backgrounds.push_back(bg);

}


void LTexture::createRect(SDL_Texture* texture, int x, int y, int WIDTH, int HEIGHT) {
	MyRect rect = { NULL, NULL };
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = WIDTH;
	stretchRect.h = HEIGHT;
	rect.stretchRect = stretchRect;
	rect.texture = texture;
	
	backgroundRects.push_back(rect);
}

