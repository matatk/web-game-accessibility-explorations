#ifndef _MENU_P_H_
#define _MENU_P_H_

typedef struct item Item;
typedef struct menu Menu;

Item *new_item(const char *, Menu *);
Menu *new_menu(int, ...);

#endif
