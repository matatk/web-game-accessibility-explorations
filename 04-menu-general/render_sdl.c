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

const int LINE_HEIGHT = 24;
const int INDENT = 24;
const int LINE_SPACING = LINE_HEIGHT * 1.5;

// State

static int vertical_pos = 0;
static bool in_horizontal_container = false;
static int horizontal_pos = 0;

// Internal API

static void render_container_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
static void render_widgety_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);
static void render_widget(SDL_Surface *screen, Page *page, int depth, Widget *widget);

// Getting sizes of surfaces

static int
get_widget_width(const int depth) {
	if (in_horizontal_container) {
		return (DRY_WIDTH - (depth * INDENT)) / 2;
	}
	return DRY_WIDTH - (depth * INDENT);
}

static int
get_widget_height() {
	return LINE_HEIGHT;
}

static SDL_Surface *
make_widget_surface(depth) {
	return SDL_CreateRGBSurface(0, get_widget_width(depth), get_widget_height(), 32, 0, 0, 0, 0);
}

// Rendering focus

static SDL_Color
get_fg_colour_based_on_focus(Page *page, Widget *widget) {
	return (widget == page->focused)
		? (SDL_Color) { 255, 255, 255 }
		: (SDL_Color) { 0xF0, 0, 0xF0 };
}

// Rendering Text

static void
render_string(SDL_Surface *surface, Page *page, Widget *widget, const char *string) {
	TTF_Font *font = TTF_OpenFont(FONT, LINE_HEIGHT);
	if (font == NULL) {
		printf("TTF loading error: %s\n", TTF_GetError());
		return;
	}

	SDL_Color fg = get_fg_colour_based_on_focus(page, widget);
	SDL_Surface *text_surface = TTF_RenderText_Blended(font, string, fg);
	SDL_BlitSurface(text_surface, NULL, surface, NULL);
	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
}

// Rendering widgets: support

static SDL_Rect
get_pos_rect(const int depth) {
	const int x_pos = INDENT + (INDENT * depth); // FIXME harmonise????
	const int y_pos = LINE_HEIGHT + (vertical_pos * LINE_SPACING);

	if (in_horizontal_container) {
		const int extra_x_pos = horizontal_pos * (get_widget_width(depth) / 2);
		SDL_Rect pos = { x_pos + extra_x_pos, y_pos, 0, 0 };
		horizontal_pos++;
		return pos;
	}

	SDL_Rect pos = { x_pos, y_pos, 0, 0 };
	vertical_pos++;
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

	in_horizontal_container = wc->orientation == HORIZONTAL;

	if (wc->parent == NULL) {
		asprintf(&string, "=== %s ===\n", wc->name);
		render_string_for_container(screen, page, widget, string, depth);
	}

	for (int i = 0; i < wc->length; i++) {
		render_widget(
			screen,
			page,
			in_horizontal_container ? depth : depth + 1,
			wc->widgets[i]);
	}

	if (in_horizontal_container) vertical_pos++;
	in_horizontal_container = false;
	horizontal_pos = 0;
}

// Rendering widgets: widgets

static void
render_slider(SDL_Surface *surface, Page *page, WidgetSlider *slider) {
	const int width = surface->w;
	const int height = surface->h;
	const float percentage =
		(float)(slider->value - slider->value_min) / (float)(slider->value_max - slider->value_min);

	SDL_Color fg = get_fg_colour_based_on_focus(page, AS_WIDGET(slider));

	SDL_Rect pos_axis = { 0, height / 2, width, 1 };
	SDL_FillRect(surface, &pos_axis, SDL_MapRGB(surface->format, fg.r, fg.g, fg.b));

	SDL_Rect pos_start = { 0, 0, 1, height };
	SDL_FillRect(surface, &pos_start, SDL_MapRGB(surface->format, fg.r, fg.g, fg.b));

	SDL_Rect pos_middle = { width / 2, 0, 1, height };
	SDL_FillRect(surface, &pos_middle, SDL_MapRGB(surface->format, fg.r, fg.g, fg.b));

	SDL_Rect pos_end = { width - 1, 0, 1, height };
	SDL_FillRect(surface, &pos_end, SDL_MapRGB(surface->format, fg.r, fg.g, fg.b));

	int cursor_x = width * percentage;
	if (cursor_x == width) cursor_x -= 4;
	SDL_Rect pos_cursor = { cursor_x, 0, 4, height };
	SDL_FillRect(surface, &pos_cursor, SDL_MapRGB(surface->format, fg.r, fg.g, fg.b));
}

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
		render_slider(rendered_widget, page, AS_WIDGET_SLIDER(widget));
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

	vertical_pos = 0;
}
