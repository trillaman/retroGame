#pragma once

#ifndef CHOOSEPLAYER_H
#define CHOOSEPLAYER_H

#include "SDL.h"
#include "GameState.h"
#include "LTexture.h"
#include "GameEngine.h"

class c_ChoosePlayer : public c_GameState
{
public:
	void Init(c_GameEngine* game);
	void Cleanup();

	void Close(c_GameEngine* game);

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



protected:
	c_ChoosePlayer() { }

private:
	static c_ChoosePlayer m_ChoosePlayer;

	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;

	SDL_Renderer* renderer = NULL;

	LTexture mBackgroundTexture;
	LTexture mForeGroundTexture;
	LTexture mTreesTexture;
};

#endif