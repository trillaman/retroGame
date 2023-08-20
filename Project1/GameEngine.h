
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SDL.h"

#include <vector>
using namespace std;

class c_GameState;

class c_GameEngine
{
public:

	void Init(const char* title, int width = 800, int height = 600, bool fullscreen = false);
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

	int screenWidth;
	int screenHeight;
	
	static c_GameEngine* Instance() {
		return &m_GameEngine;
	}
	
	SDL_Renderer* GetRenderer() const {
		if (renderer == NULL) {
			printf("Renderer is null\n");
		}
		return renderer;
	}

private:
	// the stack of states
	vector<c_GameState*> states;
	static c_GameEngine m_GameEngine;
	bool m_running;
	bool m_fullscreen;
};

#endif
