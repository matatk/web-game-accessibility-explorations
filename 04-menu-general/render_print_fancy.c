#include <stdio.h>
// FIXME use macro defn for padding

#include "menu.h"

void render_menu(Menu *menu) {
	printf("---======<<<<<< MENU >>>>>>======---\n");
	for (int i = 0; i < menu->length; i++) {
		printf("|   %s %-22s %-3s   |\n",
			i == menu->current ? "+" : " ",
			menu->items[i]->name,
			menu->items[i]->sub_menu != NULL ? ">>>" : "");
	}
	printf("---======<<<<<<~~~~~~>>>>>>======---\n");
}
