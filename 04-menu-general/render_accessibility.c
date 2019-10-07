#include <stdio.h>
#include <stdbool.h>

#include "menu.h"

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
		accessibility_render_menu_item(
			menu->items[i]->name, menu->items[i]->sub_menu != NULL);
	}

	accessibility_render_menu_done();
}

void expose_current_item(Menu *menu) {
	accessibility_render_current_item(menu, menu->current);
}

#endif
