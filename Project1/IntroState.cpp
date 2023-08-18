#include "IntroState.h"
#include "GameEngine.h"
#include "GameState.h"
#include "ExitState.h"
#include <iostream>
c_IntroState c_IntroState::m_IntroState;


void c_IntroState::Init() {
	printf("IntroState Init\n");
}

void c_IntroState::Cleanup() {
	printf("IntroState Cleanup\n");
}

void c_IntroState::Pause() {
	printf("IntroState Pause\n");
}

void c_IntroState::Resume() {
	printf("IntroState Resume\n");
}

void c_IntroState::HandleEvents(c_GameEngine* game) {
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN) {
			game->Quit();
		}
		
	}
}

void c_IntroState::Update(c_GameEngine* game) {
	//SDL_UpdateWindowSurface(game->window);
}

void c_IntroState::Draw(c_GameEngine* game) {
	printf("Draw\n");
	//SDL_UpdateWindowSurface(game->window);
}