#ifndef _MENU_H_
#define _MENU_H_

// Public

//const int MAX_ITEM_NAME_SIZE = 23;
#define MAX_ITEM_NAME_SIZE 23

typedef struct Menu Menu;
void menu_down(Menu *);
void menu_up(Menu *);
Menu *menu_activate(Menu *);
Menu *menu_back(Menu *);

Menu *new_menu(int, ...);
typedef struct ButtonWidget ButtonWidget;
typedef struct SubmenuWidget SubmenuWidget;
ButtonWidget *new_widget_button(const char *);
SubmenuWidget *new_widget_submenu(const char *, Menu *);


// Private

typedef const char * klassname;

typedef struct Widget {
	klassname classname;
	char name[MAX_ITEM_NAME_SIZE];
} Widget;

typedef struct SubmenuWidget {
	Widget base;
	Menu *sub_menu;
} SubmenuWidget;

typedef struct ButtonWidget {
	Widget base;
} ButtonWidget;


typedef struct Menu {
	int length;
	int current;
	Widget **items;
	Menu *parent_menu;
} Menu;

#endif
