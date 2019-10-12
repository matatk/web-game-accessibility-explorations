#include <stdlib.h>
#include <stdio.h>

#include "widgetbutton.h"

void button_widget_debug_print(const Widget *widget) {
	printf("[%s]", widget->name);
}

WidgetButton *new_widget_button(const char *name) {
	WidgetButton *new = malloc(sizeof(WidgetButton));
	new->base.name = name;
	new->base.type = BUTTON;

	WidgetMethods *methods = malloc(sizeof(WidgetMethods));
	methods->debug_print = &button_widget_debug_print;
	new->base.methods = methods;

	return new;
}
