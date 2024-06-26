
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameEngine.h"
#include "MyScene.h"

class c_GameState
{
public:
	virtual void Init(c_GameEngine* game) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(c_GameEngine* game) = 0;
	virtual void Update(c_GameEngine* game) = 0;
	virtual void Draw(c_GameEngine* game) = 0;

	void ChangeState(c_GameEngine* game, c_GameState* state) {
		game->ChangeState(state);
	}

	MyScene myscene;



protected:
	c_GameState() { }
};

#endif