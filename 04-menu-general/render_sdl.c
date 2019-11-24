#include <stdbool.h> // horizontal flag
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

// Constants

const int DRY_WIDTH = 640;
const int DRY_HEIGHT = 480;

const int BASE_HEIGHT = 24;
const int INDENT = 24;
const int LINE_HEIGHT = BASE_HEIGHT * 1.5;

// State

static int line_pos = 0;
static bool horizontal_container = false;
static int horizontal_pos = 0;

// Internal API

static void render_container_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
static void render_widgety_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
static void render_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);

// Getting sizes of surfaces

static int
get_widget_width(const int depth) {
	return DRY_WIDTH - depth * INDENT;
}

static int
get_widget_height() {
	return BASE_HEIGHT;
}

static SDL_Surface *
make_widget_surface(depth) {
	return SDL_CreateRGBSurface(0, get_widget_width(depth), get_widget_height(), 32, 0, 0, 0, 0);
}

// Rendering Text

static void
render_string(SDL_Surface *surface, Page *page, Widget *widget, const char *string) {
	TTF_Font *font = TTF_OpenFont(FONT, BASE_HEIGHT);
	if (font == NULL) {
		printf("TTF loading error: %s\n", TTF_GetError());
		return;
	}

	SDL_Color fg = (widget == page->focused)
		? (SDL_Color) { 255, 255, 255 }
		: (SDL_Color) { 0xF0, 0, 0xF0 };

	SDL_Surface *text_surface = TTF_RenderText_Blended(font, string, fg);
	SDL_BlitSurface(text_surface, NULL, surface, NULL);
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
}

// Rendering widgets: support

static SDL_Rect
get_pos_rect(const int depth) {
	const int base_x_pos = INDENT + (INDENT * depth);
	const int y_pos = BASE_HEIGHT + (line_pos * LINE_HEIGHT);

	if (horizontal_container) {
		const int extra_x_pos = horizontal_pos * (get_widget_width(depth) / 3);
		SDL_Rect pos = { base_x_pos + extra_x_pos, y_pos, 0, 0 };
		horizontal_pos++;
		return pos;
	}

	SDL_Rect pos = { base_x_pos, y_pos, 0, 0 };
	line_pos++;
	return pos;
}

// Rendering widgets: containers

static void
render_string_for_container(SDL_Surface *surface, Page *page, Widget *widget, const char *string, const int depth) {
	// FIXME DRY with render_widgety_widget
	SDL_Surface *rendered_string = make_widget_surface(depth);
	render_string(rendered_string, page, widget, string);
	SDL_Rect pos = get_pos_rect(depth);
	SDL_BlitSurface(rendered_string, NULL, surface, &pos);
	SDL_FreeSurface(rendered_string);
}

static void
render_container_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget) {
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	char *string; // FIXME free (and DRY w' others)

	horizontal_container = wc->orientation == HORIZONTAL;

	if (wc->parent == NULL) {
		asprintf(&string, "=== %s ===\n", wc->name);
		render_string_for_container(screen, page, widget, string, depth);
	}

	for (int i = 0; i < wc->length; i++) {
		render_widget(
			screen,
			page,
			horizontal_container ? depth : depth + 1,
			wc->widgets[i]);
	}

	if (horizontal_container) line_pos++;
	horizontal_container = false;
	horizontal_pos = 0;
}

// Rendering widgets: widgets

static void
render_widgety_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget) {
	char *string; // FIXME free (and DRY w' others)

	// FIXME DRY with render_string_for_container
	SDL_Surface *rendered_widget = make_widget_surface(depth);

	switch (widget->type) {
	case BUTTON:
		asprintf(&string, "[%s]\n", widget->name);
		render_string(rendered_widget, page, widget, string);
		break;
	case SUBPAGE:
		asprintf(&string, "%s >\n", widget->name);
		render_string(rendered_widget, page, widget, string);
		break;
	case LABEL:
		asprintf(&string, "%s:\n", widget->name);
		render_string(rendered_widget, page, widget, string);
		break;
	case TEXTBOX:
		asprintf(&string, "_%s_\n", widget->name);
		render_string(rendered_widget, page, widget, string);
		break;
	case SLIDER:
		asprintf(&string, "~~(%s: %d, %d, %d)~~\n", widget->name,
			(AS_WIDGET_SLIDER(widget))->value_min,
			(AS_WIDGET_SLIDER(widget))->value,
			(AS_WIDGET_SLIDER(widget))->value_max);
		render_string(rendered_widget, page, widget, string);
		break;
	default:
		asprintf(&string, "DEFAULT: %s\n", widget->name);
		render_string(rendered_widget, page, widget, string);
		break;
	}

	SDL_Rect pos = get_pos_rect(depth);
	SDL_BlitSurface(rendered_widget, NULL, screen, &pos);
	SDL_FreeSurface(rendered_widget);
}

// Rendering widgets: dispatch

static void
render_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, CONTAINER)) {
		render_container_widget(screen, page, depth, widget);
	} else {
		render_widgety_widget(screen, page, depth, widget);
	}
}

// Entry

// This requires that TTF_Init() has already been called
void
render_page(Page *page, void *thingy) {
	SDL_Surface *screen = (SDL_Surface *)thingy;

	Widget *root = page->root;
	render_widget(screen, page, 0, root);

	line_pos = 0;
}
