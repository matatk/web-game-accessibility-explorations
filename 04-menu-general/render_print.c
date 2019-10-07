#include <stdio.h>

#include "menu.h"

void render_menu(Menu *menu, void *unused) {
	for (int i = 0; i < menu->length; i++) {
		printf(" %s %s %s\n",
			i == menu->current ? "+" : " ",
			menu->items[i]->name,
			menu->items[i]->sub_menu != NULL ? ">>" : "");
	}
}
