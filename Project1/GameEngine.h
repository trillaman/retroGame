
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SDL.h"

#include <vector>
using namespace std;

class c_GameState;

class c_GameEngine
{
public:

	void Init(const char* title, int width = 640, int height = 480, bool fullscreen = false);
	void Cleanup();

	void ChangeState(c_GameState* state);
	void PushState(c_GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	SDL_Surface* screen;
	SDL_Window* window;
	SDL_Renderer* renderer;

private:
	// the stack of states
	vector<c_GameState*> states;

	bool m_running;
	bool m_fullscreen;
};

#endif
