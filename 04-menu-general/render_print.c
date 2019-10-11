#include <stdio.h>
#include <assert.h>

#include "menu.h"

void render_button(Widget *button) {
	printf("[%s]\n", button->name);
}

void render_submenu(Widget *submenu) {
	printf("%s >>\n", submenu->name);
}

void render_menu(Menu *menu, void *unused) {
	for (int i = 0; i < menu->length; i++) {
		printf(" %s ", i == menu->current ? "+" : " ");
		const Widget *current = menu->items[i];
		if (current->classname == "ButtonWidget") {
			render_button(menu->items[i]);
		} else if (current->classname == "SubmenuWidget") {
			render_submenu(menu->items[i]);
		}
	}
}
