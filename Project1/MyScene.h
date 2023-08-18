#ifndef MYSCENE_H
#define MYSCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


class MyScene {
public:
	typedef struct {
		int x;
		int y;
		SDL_Texture* texture;
	} Entity;

	void Update();
	void Render();
	void Destroy();
	void Load();
	void Unload();
	void addBackgroundLayer(SDL_Texture* texture, int posX, int posY);
	void createRect(int x, int y, int WIDTH, int HEIGHT);

	std::vector<Entity> backgrounds;
	std::vector<Entity> returnBackgrounds() { return backgrounds; }

	std::vector<SDL_Rect> backgroundRects;
	std::vector<SDL_Rect> returnRects() { return backgroundRects; }

};

#endif