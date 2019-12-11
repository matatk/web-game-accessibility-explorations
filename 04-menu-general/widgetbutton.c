#include <stdio.h>
#include <stdlib.h>

#include "widgetbutton.h"

static char *
button_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s[%s]", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods button_base_vtable = {
	.to_string = button_widget_to_string
};

// Public

WidgetButton *
widget_button_new(const char *name) {
	WidgetButton *new = malloc(sizeof(WidgetButton));
	widget_button_constructor(new, name);
	return new;
}

void
widget_button_constructor(WidgetButton *new, const char *name) {
	widget_constructor(AS_WIDGET(new), name);
	new->type = BUTTON;
	new->vtable = &button_base_vtable;
}
