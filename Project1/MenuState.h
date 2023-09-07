
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "SDL.h"
#include "GameState.h"
#include "LTexture.h"
#include "GameEngine.h"

class c_MenuState : public c_GameState
{
public:
	void Init(c_GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(c_GameEngine* game);
	void Update(c_GameEngine* game);
	void Draw(c_GameEngine* game);

	void Close(c_GameEngine* game);

	static c_MenuState* Instance() {
		return &m_MenuState;
	}

	static c_MenuState* Get() {
		return &m_MenuState;
	}



protected:
	c_MenuState() { }

private:
	static c_MenuState m_MenuState;

	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;

	SDL_Renderer* renderer = NULL;

	LTexture mBackgroundTexture;
	LTexture mForeGroundTexture;
	LTexture mTreesTexture;
	int activeButton = 0;

};

#endif