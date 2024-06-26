#include <stdio.h>

#include <SDL.h>
#include "GameEngine.h"
#include "GameState.h"
#include <SDL_mixer.h>



void c_GameEngine::Init(const char* title, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen) {
    int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    int windowFlags = 0;

	if (fullscreen) {
		windowFlags = SDL_WINDOW_FULLSCREEN;
	}

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Could not initialize SDL Audio! SDL_Error: %s\n", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (this->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    this->renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (this->renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

	m_running = true;
	printf("Init succesfull\n");
}

void c_GameEngine::Cleanup() {
	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	//IMG_Quit();
	SDL_Quit();
}

void c_GameEngine::ChangeState(c_GameState* state) {
	// cleanup the current state
    if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void c_GameEngine::PushState(c_GameState* state) {
	// pause current state
    if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void c_GameEngine::PopState() {
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

void c_GameEngine::HandleEvents() {
	// let the state handle events
	states.back()->HandleEvents(this);
}

void c_GameEngine::Update() {
	// let the state update the game
	states.back()->Update(this);
}

void c_GameEngine::Draw() {
	// let the state draw the screen
	states.back()->Draw(this);
}

void c_GameEngine::PlayMusic(const char* filename){
	this->gMusic = Mix_LoadMUS(filename);
	if (this->gMusic == NULL) {
		printf("Could not load music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(this->gMusic, 0);
}
