#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "menu/menu.h"
#include "render/render.h"

const int WIDTH = 320;
const int HEIGHT = 240;

Menu *root;
Menu *current;
SDL_Surface *screen;
int quit = 0;

int init() {
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

void display_current_menu() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0x80));
	render_menu(current, screen);
	SDL_Flip(screen);
}

void one_iter() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			printf("Quitting...\n");
			quit = 1;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					menu_up(current);
					break;

				case SDLK_DOWN:
					menu_down(current);
					break;

				case SDLK_RIGHT:
					current = menu_activate(current);
					break;

				default:
					break;
			}

			display_current_menu();
		}
	}
}

int main() {
	root = make_menus();
	current = root;

	if (init() < 0) return -1;

	printf("\nUse up/down arrow keys; right to enter a menu\n");
	display_current_menu();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(one_iter, 0, 1);
#else
	while(!quit) {
		one_iter();
	}
#endif

	TTF_Quit();
	SDL_Quit();
	return 0;
}
