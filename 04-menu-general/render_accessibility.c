#include <stdio.h>
#include <stdbool.h>

#include "menu.h"
#include "widget.h"

#ifdef __EMSCRIPTEN__

// Our custom JavaScript library functions
extern void accessibility_setup(void);
extern void accessibility_render_menu_start(Menu *);
extern void accessibility_render_menu_item(const char *, bool);
extern void accessibility_render_menu_done();
extern void accessibility_render_current_item(Menu *, int);

bool accessibility_setup_done = false;

void expose_menu(Menu *menu) {
	if (!accessibility_setup_done) {
		accessibility_setup();
		accessibility_setup_done = true;
	}

	accessibility_render_menu_start(menu);

	for (int i = 0; i < menu->length; i++) {
		Widget *item = menu->items[i];
		accessibility_render_menu_item(item->name, widget_is_a(item, SUBMENU));
	}

	accessibility_render_menu_done();
}

void expose_current_item(Menu *menu) {
	accessibility_render_current_item(menu, menu->current);
}

#endif
