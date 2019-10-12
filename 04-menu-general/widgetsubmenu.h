#ifndef _WIDGETSUBMENU_H_
#define _WIDGETSUBMENU_H_

#include "widget.h"
#include "menu.h"

typedef struct WidgetSubmenu {
	Widget base;
	Menu *sub_menu;
} WidgetSubmenu;

WidgetSubmenu *new_widget_submenu(const char *, Menu *);

#endif
