#include <stdlib.h>

#include "buttonwidget.h"

ButtonWidget *new_widget_button(const char *name) {
	ButtonWidget *new = malloc(sizeof(ButtonWidget));
	_widget_check_copy_name(name, new->base.name);
	new->base.classname = "ButtonWidget";
	return new;
}
