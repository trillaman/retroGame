
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

void LTexture::createTextRect(int x, int y, int WIDTH, int HEIGHT) {
	SDL_Rect rect = { NULL, NULL };
	rect.x = x;
	rect.y = y;
	rect.w = WIDTH;
	rect.h = HEIGHT;

	textRects.push_back(rect);
}

bool LTexture::loadText(std::string textureText, SDL_Color textColorParam, SDL_Point position, SDL_Renderer* renderer) {
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
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColorParam);

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
	createRect(text_texture, position.x, position.y, textW, textH);

	//SDL_FreeSurface(textSurface);

	return true;
}

SDL_Surface* LTexture::setTextSurface(TTF_Font* font, std::string text, SDL_Color textColor) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	if (textSurface == NULL) {
		printf("\nFailed to create text surface: %s\n", SDL_GetError());
		TTF_CloseFont(font);
		TTF_Quit();
	}

	return textSurface;

}

void LTexture::createButton(SDL_Rect rect, std::string text, std::string action, SDL_Color textColor, SDL_Point textPosition, bool active, int buttonID, int nextButton, SDL_Renderer* renderer) {


	if (TTF_Init() < 0) {
		printf("Error initializing SDL_ttf: %s", TTF_GetError());
		TTF_Quit();
		return;
	}

	TTF_Font* font;
	font = TTF_OpenFont("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Fonts\\m5x7.ttf", 24);
	if (font == NULL) {
		printf("\nFailed to load font: %s\n", SDL_GetError());
		TTF_Quit();
		return;
	}
	
	fontText = font;

	SDL_Surface* textSurface = setTextSurface(font, text, textColor);

	SDL_Texture* text_texture;
	text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (text_texture == NULL) {
		printf("\nFailed to create texture from surface: %s\n", SDL_GetError());
		TTF_Quit();
		return;
	}
	
	createTextRect(textPosition.x, textPosition.y, 0 ,0);

	MyButtons button = { rect, text, action, textColor, textPosition, active, buttonID, nextButton, text_texture };
	buttons.push_back(button);
}

void LTexture::createText(SDL_Rect rect, std::string text, SDL_Color textColor, SDL_Point textPosition, SDL_Renderer* renderer) {

	if (TTF_Init() < 0) {
		printf("Error initializing SDL_ttf: %s", TTF_GetError());
		TTF_Quit();
		return;
	}

	TTF_Font* font;
	font = TTF_OpenFont("C:\\Users\\Olek\\Documents\\SymfoniaCpp\\Project1\\retroGame\\Fonts\\m5x7.ttf", 24);
	if (font == NULL) {
		printf("\nFailed to load font: %s\n", SDL_GetError());
		TTF_Quit();
		return;
	}

	fontText = font;

	SDL_Surface* textSurface = setTextSurface(font, text, textColor);

	SDL_Texture* text_texture;
	text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (text_texture == NULL) {
		printf("\nFailed to create texture from surface: %s\n", SDL_GetError());
		TTF_Quit();
		return;
	}

	createTextRect(textPosition.x, textPosition.y, 0, 0);

	MyText textRect = { rect, text, textColor, textPosition,  text_texture };
	texts.push_back(textRect);
}


void LTexture::modifyButton(int buttonID, bool active, SDL_Color color, int activeButton, SDL_Renderer* renderer) {
	if (activeButton < 0 || activeButton >= buttons.size()) {
		printf("Button ID out of range");
		return;
	}
	buttons[buttonID].active = activeButton;
	SDL_Surface* textSurface = setTextSurface(fontText, buttons[buttonID].text, color);

	SDL_Texture* text_texture;
	text_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	buttons[buttonID].textColor = color;
	buttons[buttonID].texture = text_texture;
}

void LTexture::createRectWithColor(SDL_Color color, int x, int y, int WIDTH, int HEIGHT) {
	AlphaRect alphaRect;
	alphaRect.alpharect.x = 0;
	alphaRect.alpharect.y = 0;
	alphaRect.alpharect.w = WIDTH;
	alphaRect.alpharect.h = HEIGHT;
	alphaRect.color = color;
	 
	alphaRects.push_back(alphaRect);
}