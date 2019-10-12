#ifndef _MENU_H_
#define _MENU_H_

#include "widget.h"

typedef struct Menu Menu;


// Public

Menu *new_menu(int, ...);

void menu_down(Menu *);
void menu_up(Menu *);
Menu *menu_activate(Menu *);
Menu *menu_back(Menu *);

void debug_print_menu_tree(Menu *);


// Private

typedef struct Menu {
	int length;
	int current;
	Widget **items;
	Menu *parent_menu;
} Menu;

#endif
