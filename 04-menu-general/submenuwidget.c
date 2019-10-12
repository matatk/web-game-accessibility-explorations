#include <stdlib.h>
#include <stdio.h>

#include "submenuwidget.h"

void submenu_widget_to_string(Widget *widget) {
	printf("%s -> %p", widget->name, ((SubmenuWidget *)widget)->sub_menu);
}

SubmenuWidget *new_widget_submenu(const char *name, Menu *sub_menu) {
	SubmenuWidget *new = malloc(sizeof(SubmenuWidget));
	_widget_check_copy_name(name, new->base.name);
	new->base.classname = "SubmenuWidget";
	new->sub_menu = sub_menu;

	WidgetMethods *methods = malloc(sizeof(WidgetMethods));
	methods->to_string = &submenu_widget_to_string;
	new->base.methods = methods;

	return new;
}
