#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"
#include "widgetslider.h"

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
const int indent = 24;
const int line_height = size * 1.5;

static int ypos = 0;

// Internal API
static void render_container_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
static void render_widgety_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
static void render_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
// TODO sdl one

static void
render_string_graphically(
	SDL_Surface *screen, Page *page, Widget *widget, int depth, const char *string) {
	TTF_Font *font = TTF_OpenFont(FONT, size);
	if (font == NULL) {
		printf("TTF loading error: %s\n", TTF_GetError());
		return;
	}

	SDL_Color fg = (widget == page->focused)
		? (SDL_Color) { 255, 255, 255 }
		: (SDL_Color) { 0xF0, 0, 0xF0 };

	SDL_Surface *text = TTF_RenderText_Blended(font, string, fg);
	SDL_Rect pos = { indent + (indent * depth), size + (ypos * line_height), 0, 0 };
	SDL_BlitSurface(text, NULL, screen, &pos);
	SDL_FreeSurface(text);

	ypos++;

	SDL_Flip(screen);
	TTF_CloseFont(font);
}

static void
render_container_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget) {
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	char *string;

	asprintf(&string, "%s %s %s\n",
		wc->parent == NULL ? "===" : "---",
		wc->name,
		wc->parent == NULL ? "===" : "---");
	render_string_graphically(screen, page, widget, depth, string);

	for (int i = 0; i < wc->length; i++) {
		render_widget(screen, page, depth + 1, wc->widgets[i]);
	}
}

static void
render_widgety_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget) {
	char *string;

	switch (widget->type) {
	case BUTTON:
		asprintf(&string, "[%s]\n", widget->name);
		break;
	case SUBPAGE:
		asprintf(&string, "%s >\n", widget->name);
		break;
	case LABEL:
		asprintf(&string, "%s:\n", widget->name);
		break;
	case TEXTBOX:
		asprintf(&string, "_%s_\n", widget->name);
		break;
	case SLIDER:
		asprintf(&string, "~~(%s: %d, %d, %d)~~\n", widget->name,
			(AS_WIDGET_SLIDER(widget))->value_min,
			(AS_WIDGET_SLIDER(widget))->value,
			(AS_WIDGET_SLIDER(widget))->value_max);
		break;
	default:
		asprintf(&string, "DEFAULT: %s\n", widget->name);
		break;
	}

	render_string_graphically(screen, page, widget, depth, string);
}

static void
render_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, CONTAINER)) {
		render_container_widget(screen, page, depth, widget);
	} else {
		render_widgety_widget(screen, page, depth, widget);
	}
}

// This requires that TTF_Init() has already been called
void
render_page(Page *page, void *thingy) {
	SDL_Surface *screen = (SDL_Surface *)thingy;

	Widget *root = page->root;
	render_widget(screen, page, 0, root);

	ypos = 0;
}
