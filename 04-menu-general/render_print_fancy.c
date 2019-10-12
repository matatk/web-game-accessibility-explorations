#include <stdio.h>

#include "menu.h"
#include "widget.h"

void render_menu(Menu *menu) {
	printf("----======<<<<<< MENU >>>>>>======----\n");
	for (int i = 0; i < menu->length; i++) {
		Widget *item = menu->items[i];
		printf("|   %s %-24s %-3s   |\n",
			i == menu->current ? "+" : " ",
			item->name,
			widget_is_a(item, SUBMENU) ? ">>>" : "");
	}
	printf("----======<<<<<<~~~~~~>>>>>>======----\n");
}
