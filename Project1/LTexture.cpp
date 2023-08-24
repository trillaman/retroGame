
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"
#include "GameEngine.h"
#include <SDL_ttf.h>

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

bool LTexture::loadText(std::string textureText, SDL_Color textColorParam, SDL_Renderer* renderer) {
	if (TTF_Init() < 0) {
		printf("Error initializing SDL_ttf: %s", TTF_GetError());
		TTF_Quit();
		return false;
	}

	TTF_Font* font;
	font = TTF_OpenFont("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Fonts\\m5x7.ttf", 72);
	if (font == NULL) {
		printf("\nFailed to load font: %s\n", SDL_GetError());
		TTF_Quit();
		return false;
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "BLABLA", textColorParam);

	if (textSurface == NULL) {
		printf("\nFailed to create text surface: %s\n", SDL_GetError());
		TTF_CloseFont(font);
		TTF_Quit();
		return false;
	}
	//SDL_SetSurfaceBlendMode(textSurface, SDL_BLENDMODE_BLEND);

	SDL_Texture* text_texture;
	text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (text_texture == NULL) {
		printf("\nFailed to create texture from surface: %s\n", SDL_GetError());
		TTF_Quit();
		return false;
	}
	int textW = 0;
	int textH = 0;
	SDL_QueryTexture(text_texture, NULL, NULL, &textW, &textH);
	SDL_Rect dest = { 0, 0 , textW, textH };
	createRect(text_texture, 0, 0, textW, textH);
	
	//SDL_FreeSurface(textSurface);

	return true;
}