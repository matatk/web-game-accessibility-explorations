#ifdef __EMSCRIPTEN__

#include <stdbool.h>
#include <stdio.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"

// Our custom JavaScript library functions
extern void
accessibility_setup(void);
extern void
accessibility_render_page_start(Page *);
extern void
accessibility_render_page_item(const char *, bool);
extern void
accessibility_render_page_done();
extern void
accessibility_render_current_item(Page *, int);

// State

bool accessibility_setup_done = false;

// Internal (originally copied from render_sdl)

static void render_widget(Page *page, int depth, Widget *widget);
static bool in_horizontal_container = false;

static void
render_container_widget(Page *page, int depth, Widget *widget) {
	/*
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	char *string; // FIXME free (and DRY w' others)

	in_horizontal_container = wc->orientation == HORIZONTAL;

	if (wc->parent == NULL) {
		asprintf(&string, "%s\n", wc->name);
		render_container_header(screen, widget, string, depth);
	}
	*/
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	in_horizontal_container = wc->orientation == HORIZONTAL;
	//accessibility_render_page_item(item->name, widget_is_a(item, SUBPAGE));
	accessibility_render_page_item(wc->name, false);

	for (int i = 0; i < wc->length; i++) {
		render_widget(
			page,
			in_horizontal_container ? depth : depth + 1,
			wc->widgets[i]);
	}

	/*
	if (in_horizontal_container) vertical_pos++;
	in_horizontal_container = false;
	horizontal_pos = 0;
	*/
}

static void
render_widgety_widget(Page *page, int depth, Widget *widget) {
	char *string; // FIXME free (and DRY w' others)

	// FIXME DRY with render_container_header
	//SDL_Surface *rendered_widget = make_widget_surface(depth);

	switch (widget->type) {
	case BUTTON:
		asprintf(&string, "[%s]\n", widget->name);
		//render_string(rendered_widget, page, widget, string);
		accessibility_render_page_item(string, false);
		break;
	case SUBPAGE:
		asprintf(&string, "%s >\n", widget->name);
		//render_string(rendered_widget, page, widget, string);
		accessibility_render_page_item(string, true);
		break;
	case LABEL:
		asprintf(&string, "%s:\n", widget->name);
		//render_string(rendered_widget, page, widget, string);
		accessibility_render_page_item(string, false);
		break;
	case TEXTBOX:
		//render_textbox(rendered_widget, page, widget);
		accessibility_render_page_item(string, false);
		break;
	case SLIDER:
		//render_slider(rendered_widget, page, AS_WIDGET_SLIDER(widget));
		accessibility_render_page_item(string, false);
		break;
	default:
		/*
		asprintf(&string, "BASE WIDGET: %s\n", widget->name);
		render_string(rendered_widget, page, widget, string);
		*/
		//render_string(rendered_widget, page, widget, widget->name);
		accessibility_render_page_item(string, false);
		break;
	}

	/*
	SDL_Rect pos = get_pos_rect(depth);
	SDL_BlitSurface(rendered_widget, NULL, screen, &pos);
	SDL_FreeSurface(rendered_widget);
	*/
}

static void
render_widget(Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, CONTAINER)) {
		render_container_widget(page, depth, widget);
	} else {
		render_widgety_widget(page, depth, widget);
	}
}

// Entry

void
expose_page(Page *page) {
	if (!accessibility_setup_done) {
		accessibility_setup();
		accessibility_setup_done = true;
	}

	accessibility_render_page_start(page);

	/*
	for (int i = 0; i < page->length; i++) {
		Widget *item = page->items[i];
		accessibility_render_page_item(item->name, widget_is_a(item, SUBPAGE));
	}
	*/
	Widget *root = page->root;
	render_widget(page, 0, root);

	accessibility_render_page_done();
}

void
expose_current_item(Page *page) {
	// accessibility_render_current_item(page, page->current);
}

#endif
