#ifndef _MENU_P_H_
#define _MENU_P_H_

#define MAX_ITEM_NAME_SIZE 23

typedef struct Menu Menu;

typedef struct MenuItem {
	char name[MAX_ITEM_NAME_SIZE];
	Menu *sub_menu;
} MenuItem;

typedef struct Menu {
	int length;
	int current;
	MenuItem **items;
	Menu *parent_menu;
} Menu;

Menu *new_menu(int, ...);
MenuItem *new_menu_item(const char *, Menu *);

#endif
