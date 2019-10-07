#ifndef _MENU_H_
#define _MENU_H_

#include "menu_p.h"

void menu_down(Menu *);
void menu_up(Menu *);
Menu *menu_activate(Menu *);
Menu *menu_back(Menu *);

void debug_print_menu_tree(Menu *);

#endif
