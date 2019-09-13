#ifndef _MENU_P_H_
#define _MENU_P_H_

typedef struct MenuItem MenuItem;
typedef struct Menu Menu;

MenuItem *new_menu_item(const char *, Menu *);
Menu *new_menu(int, ...);

#endif
