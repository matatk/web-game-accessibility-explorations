#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "menu.h"

const int MAX_ITEM_NAME_SIZE = 22;

typedef struct item {
	char name[MAX_ITEM_NAME_SIZE];
	Menu *link;
} Item;

typedef struct menu {
	int length;
	Item **items;
} Menu;

Item *new_item(const char *name, Menu *link) {
	Item *new = malloc(sizeof(Item));
	size_t name_len = strnlen(name, MAX_ITEM_NAME_SIZE);
	if (name_len >= MAX_ITEM_NAME_SIZE) {
		printf("Warning: menu item '%s' is too long (>=%d); truncating.\n",
			name, MAX_ITEM_NAME_SIZE);
		// TODO return nowt, or something with error?
	}
	strncpy(new->name, name, MAX_ITEM_NAME_SIZE);
	new->link = link;
	return new;
}

Menu *new_menu(int length, ...) {
	va_list list;

	Menu *new = malloc(sizeof(Menu));
	new->length = length;
	new->items = malloc(length * sizeof(Item *));

	va_start(list, length);
	for (int i = 0; i < length; i++) {
		new->items[i] = va_arg(list, Item *);
	}
	va_end(list);

	return new;
}

void print_menu(Menu *menu, int depth) {
	for (int i = 0; i < menu->length; i++) {
		for (int d = 0; d < depth; d++) printf("\t");
		printf("%d: %s -> %p\n",
			i, menu->items[i]->name, menu->items[i]->link);
		if (menu->items[i]->link != NULL) {
			print_menu(menu->items[i]->link, depth + 1);
		}
	}
}

Menu *make_menus() {
	Menu *episode_menu = new_menu(3,
		new_item("Big pile of great dread", NULL),
		new_item("The floors look swell", NULL),
		new_item("Some Pearnod", NULL));

	Menu *player_options_menu = new_menu(2,
		new_item("Name", NULL),
		new_item("Colour", NULL));

	Menu *options_menu = new_menu(5,
		new_item("Player", player_options_menu),
		new_item("Controls", NULL),
		new_item("Gameplay", NULL),
		new_item("Sound", NULL),
		new_item("Video", NULL));

	Menu *main_menu = new_menu(3,
		new_item("New game", episode_menu),
		new_item("Options", options_menu),
		new_item("Exit", NULL));

	return main_menu;
}
