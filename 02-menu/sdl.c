#include <stdlib.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>

#include "menu/menu.h"
#include "render/render.h"

const int WIDTH = 320;
const int HEIGHT = 240;

// FIXME tidy up
Menu *root;
Menu *current;

// FIXME process the return value
int init() {
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
}

void one_iter() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			exit(0);
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					printf("<UP>\n");
					menu_up(current);
					break;

				case SDLK_DOWN:
					printf("<DOWN>\n");
					menu_down(current);
					break;

				case SDLK_RIGHT:
					printf("<ENTER>\n");
					current = menu_activate(current);
					break;

				case SDLK_q:
					printf("<Quitting...>\n");
					exit(0);
					break;  // FIXME needed?

				default:
					printf("<unhandled input>\n");
			}

			render_menu(current);
		}
	}
}

int main() {
	root = make_menus();
	current = root;

	init();

	debug_print_menu_tree(current);

	printf("\nUse up/down arrow keys; right to enter a menu; q to quit\n");
	render_menu(current);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(one_iter, 60, 1);
#else
	while(1) {
		one_iter();
	}
#endif

	return 0;
}
