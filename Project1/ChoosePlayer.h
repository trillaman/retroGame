#pragma once

#ifndef CHOOSEPLAYER_H
#define CHOOSEPLAYER_H

#include "SDL.h"
#include "GameState.h"
#include "LTexture.h"
#include "GameEngine.h"
#include "Character.h"

class c_ChoosePlayer : public c_GameState
{
public:
	void Init(c_GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(c_GameEngine* game);
	void Update(c_GameEngine* game);
	void Draw(c_GameEngine* game);
	
	static c_ChoosePlayer* Instance() {
		return &m_ChoosePlayer;
	}

	static c_ChoosePlayer* Get() {
		return &m_ChoosePlayer;
	}

	int getCurrentAnimFrame() {
		return currentAnimFrame;
	}

	void setCurrentAnimFrame(int frame) {
		currentAnimFrame = frame;
	}

	std::vector<Character*> characters;


protected:
	c_ChoosePlayer() { }

private:
	static c_ChoosePlayer m_ChoosePlayer;

	SDL_Surface* bg = NULL;
	SDL_Surface* fader = NULL;
	int alpha = 0;

	SDL_Renderer* renderer = NULL;

	LTexture mBackgroundTexture = LTexture();
	LTexture mForeGroundTexture = LTexture();
	LTexture mTreesTexture = LTexture();

	void Close(c_GameEngine* game);

	//int threadFunction(void* frame);

	int currentAnimFrame = 0;

	
};

#endif