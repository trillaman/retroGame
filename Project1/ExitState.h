
#ifndef EXITSTATE_H
#define EXITSTATE_H

#include "SDL.h"
#include "GameState.h"

class c_ExitState : public c_GameState
{
public:
	void Init(c_GameEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(c_GameEngine* game);
	void Update(c_GameEngine* game);
	void Draw(c_GameEngine* game);

	static c_ExitState* Instance() {
		return &m_ExitState;
	}

	static c_ExitState* Get() {
		return &m_ExitState;
	}


protected:
	c_ExitState() { }

private:
	static c_ExitState m_ExitState;

	SDL_Surface* bg;
	SDL_Surface* fader;
	int alpha;
};

#endif