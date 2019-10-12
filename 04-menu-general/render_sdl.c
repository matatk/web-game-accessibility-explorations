#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "menu.h"
#include "widget.h"

#ifdef __EMSCRIPTEN__
#define FONT "ARIAL.TTF"
#else
#ifdef __APPLE__
#define FONT "/Library/Fonts/Comic Sans MS.ttf"
#else
#define FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#endif
#endif

const int size = 24;

// This requires that TTF_Init() has already been called
void render_menu(Menu *menu, void *thingy) {
	SDL_Surface *screen = (SDL_Surface *)thingy;

	TTF_Font* font = TTF_OpenFont(FONT, size);
	if (font == NULL) {
		printf("TTF loading error: %s\n", TTF_GetError());
		return;
	}

	for (int i = 0; i < menu->length; i++) {
		char *string;
		Widget *item = menu->items[i];

		asprintf(&string, "%s %s",
			item->name,
			widget_is_a(item, SUBMENU) ? ">>" : "");

		SDL_Color fg = (i == menu->current)
			? (SDL_Color){ 255, 255, 255 }
			: (SDL_Color){ 0xF0, 0, 0xF0 };

		SDL_Surface *text = TTF_RenderText_Blended(font, string, fg);
		SDL_Rect pos = { 10, size + (i * size * 1.5), 0, 0 };
		SDL_BlitSurface(text, NULL, screen, &pos);
		SDL_FreeSurface(text);
	}

	SDL_Flip(screen);
	TTF_CloseFont(font);
}
