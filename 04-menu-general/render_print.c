#include <stdio.h>
#include <assert.h>

#include "menu.h"
#include "widget.h"

void render_menu(Menu *menu, void *unused) {
	for (int i = 0; i < menu->length; i++) {
		printf(" %s ", i == menu->current ? "+" : " ");
		const Widget *current = menu->items[i];
		widget_to_string(current);
		printf("\n");
	}
}
