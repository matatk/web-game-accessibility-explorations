#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

const int WIDTH = 320;
const int HEIGHT = 240;

int main() {
	printf("Hello, world!\n");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialisation error: %s\n", SDL_GetError());
		return 42;
	}

	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;

	window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("SDL window creation error: %s\n", SDL_GetError());
		return 43;
	}

	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0x80, 0));
	SDL_UpdateWindowSurface(window);

#ifndef __EMSCRIPTEN__
	// macOS requires an event loop to display anything
	// <found on StackOverflow>
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				quit = true;
			}
		}
	}
#endif

	// TODO what happens if this isn't called?
	//SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
