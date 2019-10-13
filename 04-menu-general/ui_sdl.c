#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "page.h"
#include "render.h"

const int WIDTH = 640;
const int HEIGHT = 480;

Page* root;
Page* current;
SDL_Surface* screen;
int quit = 0;

// Private

void
display_current_page() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0x80));
	render_page(current, screen);
	SDL_Flip(screen);
#ifdef __EMSCRIPTEN__
	expose_page(current);
	expose_current_item(current);
#endif
}

void
one_iter() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			printf("Quitting...\n");
			quit = 1;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				page_up(current);
				break;

			case SDLK_DOWN:
				page_down(current);
				break;

			case SDLK_RIGHT:
				current = page_activate(current);
				break;

			case SDLK_LEFT:
				current = page_back(current);
				break;

			default:
				break;
			}

			display_current_page();
		}
	}
}

// Public

int
ui_init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL initialisation error: %s\n", SDL_GetError());
		return -42;
	}

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("SDL screen initialisation error: %s\n", SDL_GetError());
		return -43;
	}

	if (TTF_Init() < 0) {
		printf("TTF initialisation error: %s\n", TTF_GetError());
		return -44;
	}

	return 0;
}

int
ui_start(Page* page) {
	current = page;

	display_current_page();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(one_iter, 0, 1);
#else
	while (!quit) {
		one_iter();
	}
#endif

	TTF_Quit();
	SDL_Quit();
	return 0;
}
