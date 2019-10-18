#include <stdio.h>
#include <stdlib.h>

#include "widgettextbox.h"

static void
textbox_widget_debug_print(const Widget *widget) {
	printf("[__%s__]", widget->name);
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
