#include <stdio.h>
#include <stdlib.h>

#include "widgettextbox.h"

static char *
text_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s[__%s__]", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods text_base_vtable = {
	.to_string = text_widget_to_string
};

// Public

WidgetText *
widget_text_new(const char *name) {
	WidgetText *new = malloc(sizeof(WidgetText));
	widget_text_constructor(new, name);
	return new;
}

void
widget_text_constructor(WidgetText *new, const char *name) {
	widget_constructor(AS_WIDGET(new), name);
	new->type	= TEXTBOX;
	new->vtable = &text_base_vtable;
}
