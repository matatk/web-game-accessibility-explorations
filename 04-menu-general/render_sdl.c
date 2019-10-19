#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"

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

// Internal API
static void render_container_widget(Page *page, int depth, Widget *widget);
static void render_widgety_widget(Page *page, int depth, Widget *widget);
static void render_widget(Page *page, int depth, Widget *widget);

static void
render_container_widget(Page *page, int depth, Widget *widget) {
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	for (int i = 0; i < depth; i++) printf(" ");
	printf("--- %s ---\n", wc->name);
	for (int i = 0; i < wc->length; i++) {
		render_widget(page, depth + 1, wc->widgets[i]);
	}
}

static void
render_widgety_widget(Page *page, int depth, Widget *widget) {
	for (int i = 0; i < depth; i++) printf(" ");
	printf("%s ", widget == page->focused ? "+" : " ");
	switch (widget->type) {
	case BUTTON:
		printf("[%s]\n", widget->name);
		break;
	case SUBPAGE:
		printf("%s >\n", widget->name);
		break;
	case LABEL:
		printf("%s:\n", widget->name);
		break;
	case TEXTBOX:
		printf("_%s_\n", widget->name);
		break;
	case SLIDER:
		printf("~~%s~~\n", widget->name);
		break;
	default:
		printf("DEFAULT: %s\n", widget->name);
		break;
	}
}

static void
render_widget(Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, CONTAINER)) {
		render_container_widget(page, depth, widget);
	} else {
		render_widgety_widget(page, depth, widget);
	}
}

// This requires that TTF_Init() has already been called
void
render_page(Page *page, void *thingy) {
	SDL_Surface *screen = (SDL_Surface *)thingy;

	TTF_Font *font = TTF_OpenFont(FONT, size);
	if (font == NULL) {
		printf("TTF loading error: %s\n", TTF_GetError());
		return;
	}

	Widget *root = page->root;
	render_widget(page, 0, root);

	/*
	for (int i = 0; i < page->length; i++) {
		char *string;
		Widget *item = page->items[i];

		asprintf(&string, "%s %s",
			item->name,
			widget_is_a(item, SUBPAGE) ? ">>" : "");

		SDL_Color fg = (i == page->current)
			? (SDL_Color) { 255, 255, 255 }
			: (SDL_Color) { 0xF0, 0, 0xF0 };

		SDL_Surface *text = TTF_RenderText_Blended(font, string, fg);
		SDL_Rect pos = { 10, size + (i * size * 1.5), 0, 0 };
		SDL_BlitSurface(text, NULL, screen, &pos);
		SDL_FreeSurface(text);
	}
	*/

	SDL_Flip(screen);
	TTF_CloseFont(font);
}
