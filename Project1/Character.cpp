#include "Character.h"



void Character::PlayIdleAnimation() {
	//SDL_RenderCopy(renderer, texture, &rect, &rect);
}

void Character::PlayWalkAnimation() {
	//SDL_RenderCopy(renderer, texture, &rect, &rect);
}

void Character::PlayJumpAnimation() {
	//SDL_RenderCopy(renderer, texture, &rect, &rect);
}

void Character::PlayPunchAnimation() {
	//SDL_RenderCopy(renderer, texture, &rect, &rect);
}

void Character::PlayKickAnimation() {
	//SDL_RenderCopy(renderer, texture, &rect, &rect);
}

void Character::CleanupCharacter() {
	//SDL_DestroyTexture(texture);
}

Character::Character(std::string name, int posX, int posY) {
	this->name = name;
	this->posX = posX;
	this->posY = posY;
}
