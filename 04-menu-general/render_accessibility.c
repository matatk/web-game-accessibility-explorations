#ifdef __EMSCRIPTEN__

#include <stdbool.h>
#include <stdio.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"
#include "widgetslider.h"
#include "widgettextbox.h"

// Our custom JavaScript library functions
extern void
accessibility_setup(void);
extern void
accessibility_render_page_start();
extern void
accessibility_render_item(const char *, const int, const Widget *, const Widget *);
extern void
accessibility_render_page_done();
extern void
accessibility_set_focus(Widget *);

// State

static bool accessibility_setup_done = false;

// Internal

static void render_widget(Page *page, int depth, Widget *widget);
static bool in_horizontal_container = false;

static void
render_container_widget(Page *page, int depth, Widget *widget) {
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	in_horizontal_container = wc->orientation == HORIZONTAL;

	accessibility_render_item(wc->name, CONTAINER, widget, wc->parent);

	for (int i = 0; i < wc->length; i++) {
		render_widget(
			page,
			in_horizontal_container ? depth : depth + 1,
			wc->widgets[i]);
	}
}

static void
render_widgety_widget(Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, TEXTBOX)) {
		WidgetText *textbox = AS_WIDGET_TEXTBOX(widget);
		accessibility_render_item(textbox->value, widget->type, widget, widget->parent);
	} else {
		accessibility_render_item(widget->name, widget->type, widget, widget->parent);
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
	accessibility_set_focus(page->focused);
}

#endif
