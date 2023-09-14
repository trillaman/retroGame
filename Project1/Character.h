
#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL.h"
#include <string>
#include <SDL_image.h>


class Character
{
public:
	void PlayKickAnimation();
	void PlayPunchAnimation();
	void PlayJumpAnimation();
	void PlayWalkAnimation();
	void PlayIdleAnimation();

	void CleanupCharacter();

	Character(std::string name, int posX, int posY);

	static Character* Instance() {
		return &m_Character;
	}

	void setWidth(int w) {
		this->w = w;
	}

	void setHeight(int h) {
		this->h = h;
	}

	void setNameWidth(int w) {
		this->nameWidth = w;
	}

	void setNameHeight(int h) {
		this->nameHeight = h;
	}

	std::string getName() {
		return name;
	}

	int getNameWidth() {
		return nameWidth;
	}

	std::string idleAnimPath = "";
	std::string puchAnimPath = "";
	std::string kickAnimPath = "";
	std::string jumpAnimPath = "";
	std::string walkAnimPath = "";


	IMG_Animation* idleAnim = NULL;
	IMG_Animation* punchAnim = NULL;
	IMG_Animation* kickAnim = NULL;
	IMG_Animation* jumpAnim = NULL;
	IMG_Animation* walkAnim = NULL;

	int getPosX() {
		return posX;
	}

	int getPosY() {
		return posY;
	}

	void setPosX(int x) {
		posX = x;
	}

	void setPosY(int y) {
		posY = y;
	}


	SDL_Texture** getAnimTextures() {
		return idleAnimTextures;
	}

	SDL_Texture** animTextures;

	int getWidth() {
		return w;
	}

	int getHeight() {
		return h;
	}

	void setCurrentAnimFrame(int frame) {
		current_frame = frame;
	}

	int getCurrentAnimFrame(){
		return current_frame;
	}


	int count = 0;

	int delay = 0;

	SDL_Texture** idleAnimTextures;

	int current_frame = 0;

private:
	static Character m_Character;

	SDL_Texture* texture;
	SDL_Rect* rect;


	int w = 0, h = 0;


	std::string name = "";

	int posX = 0, posY = 0;

	int nameWidth = 0, nameHeight = 0;


};

#endif