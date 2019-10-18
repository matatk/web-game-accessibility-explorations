#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widget.h"

static char *
base_widget_debug_print(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s<%s>", padding(depth), widget->name);
	return string;
}

static const WidgetMethods base_vtable = {
	.debug_print = base_widget_debug_print
};

// Intended for widgets only

const char *
padding(int depth) {
	char *string;
	asprintf(&string, "%*s", depth, "");
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
widget_debug_print(const Widget *widget, const int depth) {
	return widget->vtable->debug_print(widget, depth);
}
