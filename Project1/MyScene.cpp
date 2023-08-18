#include "MyScene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

void MyScene::addBackgroundLayer(SDL_Texture* texture, int posX, int posY) {
	printf("Adding background");
	Entity bg = { 0, 0, nullptr };
	memset(&bg, 0, sizeof(Entity));
	bg.x = posX;
	bg.y = posY;
	bg.texture = texture;
	this->backgrounds.push_back(bg);
}

void MyScene::createRect(int x, int y, int WIDTH, int HEIGHT) {
	SDL_Rect stretchRect;
	stretchRect.x = x;
	stretchRect.y = y;
	stretchRect.w = WIDTH;
	stretchRect.h = HEIGHT;
	this->backgroundRects.push_back(stretchRect);
}

