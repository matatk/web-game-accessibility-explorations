#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "menu.h"
#include "submenuwidget.h"

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

void _debug_print_menu_tree(Menu *menu, int depth) {
	for (int d = 0; d < depth; d++) printf("\t");
	printf("Menu: %p; Parent: %p\n", menu, menu->parent_menu);

	for (int i = 0; i < menu->length; i++) {
		for (int d = 0; d < depth; d++) printf("\t");
		Widget *item = menu->items[i];
		printf("%d: ", i);
		widget_debug_print(item);
		printf("\n");
		if (item->classname == "SubmenuWidget") {
			_debug_print_menu_tree(
				((SubmenuWidget *)item)->sub_menu, depth + 1);
		}
	}
}

void debug_print_menu_tree(Menu *menu) {
	_debug_print_menu_tree(menu, 0);
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
