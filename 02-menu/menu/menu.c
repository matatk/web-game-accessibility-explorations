#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "menu.h"

MenuItem *new_menu_item(const char *name, Menu *sub_menu) {
	MenuItem *new = malloc(sizeof(MenuItem));
	size_t name_len = strnlen(name, MAX_ITEM_NAME_SIZE);
	if (name_len > MAX_ITEM_NAME_SIZE) {
		printf("Warning: menu item '%s' is too long (>=%d); truncating.\n",
			name, MAX_ITEM_NAME_SIZE);
		// TODO return nowt, or something with error?
	}
	strncpy(new->name, name, MAX_ITEM_NAME_SIZE);
	new->sub_menu = sub_menu;
	return new;
}

Menu *new_menu(int length, ...) {
	va_list list;

	Menu *new = malloc(sizeof(Menu));
	new->length = length;
	new->current = 0;
	new->items = malloc(length * sizeof(MenuItem *));

	va_start(list, length);
	for (int i = 0; i < length; i++) {
		new->items[i] = va_arg(list, MenuItem *);
	}
	va_end(list);

	return new;
}

void _debug_print_menu_tree(Menu *menu, int depth) {
	for (int i = 0; i < menu->length; i++) {
		for (int d = 0; d < depth; d++) printf("\t");
		printf("%d: %s -> %p\n",
			i, menu->items[i]->name, menu->items[i]->sub_menu);
		if (menu->items[i]->sub_menu != NULL) {
			_debug_print_menu_tree(menu->items[i]->sub_menu, depth + 1);
		}
	}
}

void debug_print_menu_tree(Menu *menu) {
	_debug_print_menu_tree(menu, 0);
}

Menu *make_menus() {
	Menu *episode_menu = new_menu(3,
		new_menu_item("Big pile of great dread", NULL),
		new_menu_item("The floors look swell", NULL),
		new_menu_item("Some Pearnod", NULL));

	Menu *player_options_menu = new_menu(2,
		new_menu_item("Name", NULL),
		new_menu_item("Colour", NULL));

	Menu *options_menu = new_menu(5,
		new_menu_item("Player", player_options_menu),
		new_menu_item("Controls", NULL),
		new_menu_item("Gameplay", NULL),
		new_menu_item("Sound", NULL),
		new_menu_item("Video", NULL));

	Menu *main_menu = new_menu(3,
		new_menu_item("New game", episode_menu),
		new_menu_item("Options", options_menu),
		new_menu_item("Exit", NULL));

	return main_menu;
}

void menu_down(Menu *menu) {
	menu->current = (menu->current + 1) % menu->length;
}

void menu_up(Menu *menu) {
	menu->current = menu->current == 0
		? menu->length - 1
		: menu->current - 1;
}

Menu *menu_activate(Menu *menu) {
	if (menu->items[menu->current]->sub_menu != NULL) {
		return menu->items[menu->current]->sub_menu;
	} else {
		return menu;
	}
}
