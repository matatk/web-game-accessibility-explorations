#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../menu/menu.h"

#ifdef __EMSCRIPTEN__
#define FONT "ARIAL.TTF"
#else
#define FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#endif

const int size = 24;

void render_menu(Menu *menu, void *thingy) {
	SDL_Surface *screen = (SDL_Surface *)thingy;

	TTF_Font* font = TTF_OpenFont(FONT, size);
	if (font == NULL) {
		printf("TTF loading error: %s\n", TTF_GetError());
		return;
	}

	SDL_Color fg = { 255, 255, 255 };
	SDL_Color bg = {   0,   0,   0 };

	for (int i = 0; i < menu->length; i++) {
		char *string;
		asprintf(&string, "%s %s\n",
				menu->items[i]->name,
				menu->items[i]->sub_menu != NULL ? ">>" : "");

		SDL_Color fg = (i == menu->current)
			? (SDL_Color){ 255, 255, 255 }
		: (SDL_Color){ 255, 0, 255 };

		SDL_Surface *text = TTF_RenderText_Shaded(font, string, fg, bg);
		SDL_Rect pos = { 10, size + (i * size * 1.5), 0, 0 };
		SDL_BlitSurface(text, NULL, screen, &pos);
		SDL_FreeSurface(text);
	}

	SDL_Flip(screen);
	TTF_CloseFont(font);
}
