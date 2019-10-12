#ifndef _SUBMENUWIDGET_H_
#define _SUBMENUWIDGET_H_

#include "widget.h"
#include "menu.h"

typedef struct SubmenuWidget {
	Widget base;
	Menu *sub_menu;
} SubmenuWidget;

SubmenuWidget *new_widget_submenu(const char *, Menu *);

#endif
