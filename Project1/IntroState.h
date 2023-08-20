
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "SDL.h"
#include "GameState.h"
#include "LTexture.h"
#include "GameEngine.h"

class c_IntroState : public c_GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(c_GameEngine* game);
	void Update(c_GameEngine* game);
	void Draw(c_GameEngine* game);

	static c_IntroState* Instance() {
		return &m_IntroState;
	}

	static c_IntroState* Get() {
		return &m_IntroState;
	}



protected:
	c_IntroState() { }

private:
	static c_IntroState m_IntroState;

	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;

	SDL_Renderer* renderer = NULL;

	LTexture mBackgroundTexture;
	LTexture mForeGroundTexture;
	LTexture mTreesTexture;
};

#endif