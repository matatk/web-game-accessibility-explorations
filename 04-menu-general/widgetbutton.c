#include <stdio.h>
#include <stdlib.h>

#include "widgetbutton.h"

void
button_widget_debug_print(const Widget* widget) {
	printf("[%s]", widget->name);
}

static const WidgetMethods button_methods = {
	.debug_print = button_widget_debug_print
};

WidgetButton*
new_widget_button(const char* name) {
	WidgetButton* new = malloc(sizeof(WidgetButton));
	new->base.name = name;
	new->base.type = BUTTON;
	new->base.methods = &button_methods;
	return new;
}
