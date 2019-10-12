#include <stdlib.h>
#include <stdio.h>

#include "widgetsubmenu.h"

void submenu_widget_debug_print(const Widget *widget) {
	printf("%s -> %p", widget->name, ((WidgetSubmenu *)widget)->sub_menu);
}

WidgetSubmenu *new_widget_submenu(const char *name, Menu *sub_menu) {
	WidgetSubmenu *new = malloc(sizeof(WidgetSubmenu));
	new->base.name = name;
	new->base.type = SUBMENU;
	new->sub_menu = sub_menu;

	WidgetMethods *methods = malloc(sizeof(WidgetMethods));
	methods->debug_print = &submenu_widget_debug_print;
	new->base.methods = methods;

	return new;
}
