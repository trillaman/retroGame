#include "ExitState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "IntroState.h"

c_ExitState c_ExitState::m_ExitState;


void c_ExitState::Init(c_GameEngine* game) {
	printf("ExitState Init\n");
}

void c_ExitState::Cleanup() {
	printf("ExitState Cleanup\n");
}

void c_ExitState::Pause() {
	printf("ExitState Pause\n");
}

void c_ExitState::Resume() {
	printf("ExitState Resume\n");
}

void c_ExitState::HandleEvents(c_GameEngine* game) {
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;
			case SDLK_ESCAPE:
				game->Quit();
				break;
			case SDL_MOUSEMOTION:
				game->ChangeState(c_IntroState::Instance());
				break;
		}
	}
}

void c_ExitState::Update(c_GameEngine* game) {
	printf("ExitState update\n");
}

void c_ExitState::Draw(c_GameEngine* game) {
	SDL_UpdateWindowSurface(game->window);
}