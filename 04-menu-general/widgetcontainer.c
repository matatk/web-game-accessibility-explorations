#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "widgetcontainer.h"

void
container_widget_debug_print(const Widget *widget) {
	WidgetContainer *wc = (WidgetContainer *)widget;
	printf("<<%s>>", widget->name);
	for (int i = 0; i < wc->length; i++) {
		widget_debug_print(wc->widgets[i]);
	}
}

static const WidgetMethods container_vtable = {
	.debug_print = container_widget_debug_print
};

WidgetContainer *
new_widget_container(const char *name, int length, ...) {
	va_list list;

	WidgetContainer *new = malloc(sizeof(WidgetContainer));
	new->base.name = name;
	new->base.type = CONTAINER;
	new->base.vtable = &container_vtable;

	printf("set up widget container; starting var args\n");
	new->length = length;
	new->widgets = malloc(length * sizeof(Widget *));
	va_start(list, length);
	for (int i = 0; i < length; i++) {
		new->widgets[i] = va_arg(list, Widget *);
	}
	va_end(list);
	printf("finished var args\n");

	return new;
}
