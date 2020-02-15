#include <stdio.h>
#include <string.h>
#include <SDL.h>

#include "Maple.h"
#include "Game.h"

internal bool is_running = true;
internal Uint32 ticks_count = 0;
internal SDL_Window* window = NULL;
internal SDL_Surface* screen_surface = NULL;

// Shared with the Renderer
SDL_Renderer* sdl_renderer = NULL;
// Shared with Inputs....
Input_State input_state = { 0 };

int main(int argc, char** argv) {


	if (SDL_Init(SDL_INIT_EVERYTHING) < NULL) {
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		// Create Window
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdl_renderer == NULL) {
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return 1;
	}


	GameStart();
	ticks_count = SDL_GetTicks();

	while (is_running){
		SDL_Event sdl_event = { 0 };
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type)
			{
			case SDL_QUIT:
				is_running = false;
				break;
			default:
				break;
			}
		}

		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

		if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
			is_running = false;
		}

		for (int i = 0; i < K_COUNT; i++)
		{
			input_state.was_pressed[i] = input_state.is_pressed[i];
			input_state.is_pressed[i] = false;
		}
		// TODO BY KEYBINDING BY TABLE>>>>.
		if (keyboard_state[SDL_SCANCODE_UP]) {
			input_state.is_pressed[K_UP] = true;
		}
		if (keyboard_state[SDL_SCANCODE_DOWN]) {
			input_state.is_pressed[K_DOWN] = true;
		}
		if (keyboard_state[SDL_SCANCODE_LEFT]) {
			input_state.is_pressed[K_LEFT] = true;
		}
		if (keyboard_state[SDL_SCANCODE_RIGHT]) {
			input_state.is_pressed[K_RIGHT] = true;
		}
		if (keyboard_state[SDL_SCANCODE_SPACE]) {
			input_state.is_pressed[K_FIRE1] = true;
		}
		if (keyboard_state[SDL_SCANCODE_F]) {
			input_state.is_pressed[K_FIRE2] = true;
		}
		if (keyboard_state[SDL_SCANCODE_I]) {
			input_state.is_pressed[K_ITEM] = true;
		}


		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count + 16));\
		float deltaTime = (SDL_GetTicks() - ticks_count) / 1000.0f;
		// Clamp maximum delta time value
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}		
		SDL_SetRenderDrawColor(sdl_renderer, 20, 20, 20, 255);
		SDL_RenderClear(sdl_renderer);

		RendererDrawColorSet(20, 20, 20, 255);

		GameSimulate(deltaTime);

		SDL_RenderPresent(sdl_renderer);

		ticks_count = SDL_GetTicks();
	}

	SDL_DestroyRenderer(sdl_renderer);
	// Close and destroy the window
	SDL_DestroyWindow(window);
	// Clean up
	SDL_Quit();

	return 0;
}
