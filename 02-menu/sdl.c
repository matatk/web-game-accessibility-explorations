#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL.h>

#include "menu/menu.h"
#include "render/render.h"

const int WIDTH = 640;
const int HEIGHT = 480;

bool is(char input, const char *str) {
	return strncmp(&input, str, 1) == 0;
}

int main() {
	Menu *root = make_menus();
	Menu *current = root;
	bool quit = false;

	debug_print_menu_tree(current);

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

	printf("\nUse up/down arrow keys; right to enter a menu; q to quit\n");
	render_menu(current);

	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
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
						quit = true;
						break;

					default:
						printf("<unhandled input>\n");
				}

				render_menu(current);
			}
		}
	}

	return 0;
}
