#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "menu.h"

Menu *new_menu(int length, ...) {
	va_list list;

	Menu *new = malloc(sizeof(Menu));
	new->parent_menu = NULL;
	new->length = length;
	new->current = 0;
	new->items = malloc(length * sizeof(Widget *));

	va_start(list, length);
	for (int i = 0; i < length; i++) {
		new->items[i] = va_arg(list, Widget *);

		if (new->items[i]->classname == "SubmenuWidget") {
			((SubmenuWidget *)new->items[i])->sub_menu->parent_menu = new;
		}
	}
	va_end(list);

	return new;
}

void _check_copy_name(const char *name, char *destination) {
	size_t name_len = strnlen(name, MAX_ITEM_NAME_SIZE);
	if (name_len > MAX_ITEM_NAME_SIZE) {
		printf("Warning: menu item '%s' is too long (>=%d); truncating.\n",
			name, MAX_ITEM_NAME_SIZE);
		// TODO return nowt, or something with error?
	}
	strncpy(destination, name, MAX_ITEM_NAME_SIZE);
}

ButtonWidget *new_widget_button(const char *name) {
	ButtonWidget *new = malloc(sizeof(ButtonWidget));
	_check_copy_name(name, new->base.name);
	new->base.classname = "ButtonWidget";
	return new;
}

SubmenuWidget *new_widget_submenu(const char *name, Menu *sub_menu) {
	SubmenuWidget *new = malloc(sizeof(SubmenuWidget));
	_check_copy_name(name, new->base.name);
	new->base.classname = "SubmenuWidget";
	new->sub_menu = sub_menu;
	return new;
}

/* TODO: call teh widget's render function
void _debug_print_menu_tree(Menu *menu, int depth) {
	for (int d = 0; d < depth; d++) printf("\t");
	printf("Menu: %p; Parent: %p\n", menu, menu->parent_menu);

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
} */

void menu_down(Menu *menu) {
	menu->current = (menu->current + 1) % menu->length;
}

void menu_up(Menu *menu) {
	menu->current = menu->current == 0
		? menu->length - 1
		: menu->current - 1;
}

Menu *menu_activate(Menu *menu) {
	Widget *current = menu->items[menu->current];
	if (current->classname == "SubmenuWidget") {
		return ((SubmenuWidget *)current)->sub_menu;
	} else {
		return menu;
	}
}

Menu *menu_back(Menu *menu) {
	if (menu->parent_menu != NULL) {
		return menu->parent_menu;
	} else {
		return menu;
	}
}
