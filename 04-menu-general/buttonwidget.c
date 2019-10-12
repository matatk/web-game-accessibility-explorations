#include <stdlib.h>
#include <stdio.h>

#include "buttonwidget.h"

void button_widget_to_string(Widget *widget) {
	printf("[%s]", widget->name);
}

ButtonWidget *new_widget_button(const char *name) {
	ButtonWidget *new = malloc(sizeof(ButtonWidget));
	_widget_check_copy_name(name, new->base.name);
	new->base.classname = "ButtonWidget";

	WidgetMethods *methods = malloc(sizeof(WidgetMethods));
	methods->to_string = &button_widget_to_string;
	new->base.methods = methods;

	return new;
}
