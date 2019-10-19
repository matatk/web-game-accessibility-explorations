#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widget.h"

static char *
base_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s<%s>", widget_padding(depth), widget->name);
	return string;
}

static const WidgetMethods base_vtable = {
	.to_string = base_widget_to_string
};

// Intended for widgets only

const char *
widget_padding(int depth) {
	char *string;
	asprintf(&string, "%*s", depth * 4, "");
	return string;
}

// Public

Widget *
widget_new(const char *name) {
	Widget *new = malloc(sizeof(Widget));
	widget_constructor(new, name);
	return new;
}

void
widget_constructor(Widget *new, const char *name) {
	new->type = WIDGET;
	new->name = name;
	new->parent = NULL;
	new->vtable = &base_vtable;
}

bool
widget_is_a(const Widget *widget, WidgetType type) {
	return widget->type == type;
}

inline char *
widget_to_string(const Widget *widget, const int depth) {
	return widget->vtable->to_string(widget, depth);
}
