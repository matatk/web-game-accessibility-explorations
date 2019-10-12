#include <stdlib.h>

#include "submenuwidget.h"

SubmenuWidget *new_widget_submenu(const char *name, Menu *sub_menu) {
	SubmenuWidget *new = malloc(sizeof(SubmenuWidget));
	_widget_check_copy_name(name, new->base.name);
	new->base.classname = "SubmenuWidget";
	new->sub_menu = sub_menu;
	return new;
}
