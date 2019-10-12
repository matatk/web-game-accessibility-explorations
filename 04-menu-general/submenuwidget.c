#include <stdlib.h>
#include <stdio.h>

#include "submenuwidget.h"

void submenu_widget_debug_print(Widget *widget) {
	printf("%s -> %p", widget->name, ((SubmenuWidget *)widget)->sub_menu);
}

SubmenuWidget *new_widget_submenu(const char *name, Menu *sub_menu) {
	SubmenuWidget *new = malloc(sizeof(SubmenuWidget));
	_widget_check_copy_name(name, new->base.name);
	new->base.classname = "SubmenuWidget";
	new->sub_menu = sub_menu;

	WidgetMethods *methods = malloc(sizeof(WidgetMethods));
	methods->debug_print = &submenu_widget_debug_print;
	new->base.methods = methods;

	return new;
}
