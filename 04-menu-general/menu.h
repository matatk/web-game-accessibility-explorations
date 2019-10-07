#ifndef _MENU_H_
#define _MENU_H_

typedef struct Menu Menu;
typedef struct MenuItem MenuItem;

#define MAX_ITEM_NAME_SIZE 23

Menu *new_menu(int, ...);
MenuItem *new_menu_item(const char *, Menu *);

void menu_down(Menu *);
void menu_up(Menu *);
Menu *menu_activate(Menu *);
Menu *menu_back(Menu *);

void debug_print_menu_tree(Menu *);

#include "menu_p.h"

#endif
