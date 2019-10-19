#include <stdio.h>
#include <stdlib.h>

#include "widgetlabel.h"

static char *
label_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s-%s-", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods label_base_vtable = {
	.to_string = label_widget_to_string
};

// Public

WidgetLabel *
widget_label_new(const char *name) {
	WidgetLabel *new = malloc(sizeof(WidgetLabel));
	widget_label_constructor(new, name);
	return new;
}

void
widget_label_constructor(WidgetLabel *new, const char *name) {
	widget_constructor(AS_WIDGET(new), name);
	new->type	= LABEL;
	new->vtable = &label_base_vtable;
}
