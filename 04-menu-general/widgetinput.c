#include <stdio.h>
#include <stdlib.h>

#include "widgetinput.h"

static char *
input_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s>>%s<<", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods input_base_vtable = {
	.to_string = input_widget_to_string
};

// Public

WidgetInput *
widget_input_new(const char *name) {
	WidgetInput *new = malloc(sizeof(WidgetInput));
	widget_input_constructor(new, name);
	return new;
}

void
widget_input_constructor(WidgetInput *new, const char *name) {
	widget_constructor(AS_WIDGET(new), name);
	new->type	= INPUT;
	new->vtable = &input_base_vtable;
}
