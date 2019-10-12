#ifndef _SUBMENUWIDGET_H_
#define _SUBMENUWIDGET_H_

#include "widget.h"
#include "menu.h"

typedef struct WidgetSubmenu {
	Widget base;
	Menu *sub_menu;
} WidgetSubmenu;

WidgetSubmenu *new_widget_submenu(const char *, Menu *);

#endif
