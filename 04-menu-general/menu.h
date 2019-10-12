#ifndef _MENU_H_
#define _MENU_H_

#include "widget.h"

typedef struct Menu Menu;


// Public

void menu_down(Menu *);
void menu_up(Menu *);
Menu *menu_activate(Menu *);
Menu *menu_back(Menu *);

Menu *new_menu(int, ...);


// Private

typedef struct Menu {
	int length;
	int current;
	Widget **items;
	Menu *parent_menu;
} Menu;

#endif
