#ifdef __EMSCRIPTEN__

#include <stdbool.h>
#include <stdio.h>

#include "page.h"
#include "widget.h"

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

bool accessibility_setup_done = false;

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

	accessibility_render_page_done();
}

void
expose_current_item(Page *page) {
	// accessibility_render_current_item(page, page->current);
}

#endif
