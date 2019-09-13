#ifndef _MENU_H_
#define _MENU_H_
#include "menu_p.h"

Menu *make_menus();
void print_menu_tree(Menu *);
void print_menu(Menu *);

void menu_down(Menu *);
void menu_up(Menu *);
Menu *menu_activate(Menu *);

#endif
