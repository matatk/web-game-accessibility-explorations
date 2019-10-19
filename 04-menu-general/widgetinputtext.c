#include <stdio.h>
#include <stdlib.h>

#include "widgetinputtext.h"

static char *
text_input_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s[__%s__]", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods text_input_base_vtable = {
	.to_string = text_input_widget_to_string
};

// Public

WidgetInputText *
widget_input_text_new(const char *name) {
	WidgetInputText *new = malloc(sizeof(WidgetInputText));
	widget_input_text_constructor(new, name);
	return new;
}

void
widget_input_text_constructor(WidgetInputText *new, const char *name) {
	widget_input_constructor(AS_WIDGET_INPUT(new), name);
	new->type	= TEXTBOX;
	new->vtable = &text_input_base_vtable;
}
