#include <stdio.h>
#include <stdlib.h>

#include "widgettextbox.h"

static char *
textbox_widget_debug_print(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s[__%s__]", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods textbox_base_vtable = {
	.debug_print = textbox_widget_debug_print
};

// Public

WidgetTextbox *
widget_textbox_new(const char *name) {
	WidgetTextbox *new = malloc(sizeof(WidgetTextbox));
	widget_textbox_constructor(new, name);
	return new;
}

void
widget_textbox_constructor(WidgetTextbox *new, const char *name) {
	widget_constructor(AS_WIDGET(new), name);
	new->type = TEXTBOX;
	new->vtable = &textbox_base_vtable;
}
