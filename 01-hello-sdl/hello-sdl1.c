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

	SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("SDL screen initialisation error: %s\n", SDL_GetError());
		return 43;
	}

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0x80, 0));
	SDL_Flip(screen);

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

	SDL_Quit();
	return 0;
}
