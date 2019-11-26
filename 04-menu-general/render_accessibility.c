#ifdef __EMSCRIPTEN__

#include <stdbool.h>
#include <stdio.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"
#include "widgetslider.h"

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

static bool accessibility_setup_done = false;

// Internal

static void render_widget(Page *page, int depth, Widget *widget);
static bool in_horizontal_container = false;

static void
render_container_widget(Page *page, int depth, Widget *widget) {
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	in_horizontal_container = wc->orientation == HORIZONTAL;

	accessibility_render_page_item(wc->name, false);

	for (int i = 0; i < wc->length; i++) {
		render_widget(
			page,
			in_horizontal_container ? depth : depth + 1,
			wc->widgets[i]);
	}
}

static void
render_widgety_widget(Page *page, int depth, Widget *widget) {
	char *string;
	switch (widget->type) {
	case BUTTON:
		asprintf(&string, "[%s]\n", widget->name);
		accessibility_render_page_item(string, false);
		break;
	case SUBPAGE:
		asprintf(&string, "%s >\n", widget->name);
		accessibility_render_page_item(string, true);
		break;
	case LABEL:
		asprintf(&string, "%s:\n", widget->name);
		accessibility_render_page_item(string, false);
		break;
	case TEXTBOX:
		asprintf(&string, "_%s_\n", widget->name);
		accessibility_render_page_item(string, false);
		break;
	case SLIDER:
		WidgetSlider *slider = AS_WIDGET_SLIDER(widget);
		asprintf(&string, "~~%s (%d, %d, %d)~~\n", widget->name,
			slider->value_min, slider->value, slider->value_max);
		accessibility_render_page_item(string, false);
		break;
	default:
		asprintf(&string, "BASE WIDGET: %s\n", widget->name);
		accessibility_render_page_item(string, false);
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

// Entry

void
expose_page(Page *page) {
	if (!accessibility_setup_done) {
		accessibility_setup();
		accessibility_setup_done = true;
	}

	accessibility_render_page_start(page);

	Widget *root = page->root;
	render_widget(page, 0, root);

	accessibility_render_page_done();
}

void
expose_current_item(Page *page) {
	// accessibility_render_current_item(page, page->current);
}

#endif
