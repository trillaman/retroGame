#include "Character.h"
#include "GameEngine.h"

int Character::InitCharacter() {
	this->setNameWidth(0);

	return 0;
}

int Character::InitCharacterRect() {
	SDL_Rect rect;
	rect.x = this->getPosX();
	rect.y = this->getPosY();
	rect.w = this->getWidth();
	rect.h = this->getHeight();

	printf("Position: %d, %d\n", rect.x, rect.y);
	printf("HW: %d, %d\n", rect.w, rect.h);

	this->setRect(rect);

	return 0;
};

int Character::InitIdleAnimation(c_GameEngine* game, std::string path) {
	this->idleAnimPath = path;
	this->idleAnim = IMG_LoadAnimation(this->idleAnimPath.c_str());

	if (this->idleAnim == NULL) { //Not to be here
		printf("Couldnt load animation\n"); //Not to be here
		this->idleAnim = NULL; //Not to be here
		return 1;
	}

	if (this->idleAnim != NULL) {  //verifying if animation is loaded but whole verification could be as method
		this->idleAnimTextures = (SDL_Texture**)SDL_calloc(this->idleAnim->count, sizeof(*this->animTextures));
	}

	if (this->idleAnimTextures == NULL) {
		printf("Couldnt allocate memory\n");
		return 1;
	}
	else {
		if (this->idleAnim != NULL) {
			for (int j = 0; j < this->idleAnim->count; ++j) {
				this->idleAnimTextures[j] = SDL_CreateTextureFromSurface(game->renderer, this->idleAnim->frames[j]);
			}
		}
	}

	return 0;
}

void Character::IncreaseCurrentFrame() {
	current_frame = (current_frame + 1) % idleAnim->count;
	SDL_Delay(60);

}

SDL_Texture* Character::PlayIdleAnimation() {
	return idleAnimTextures[current_frame];
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
