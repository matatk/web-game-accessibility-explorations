#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "widgetcontainer.h"

static void
container_widget_debug_print(const Widget *widget) {
	WidgetContainer *wc = (WidgetContainer *)widget;
	printf("<<%s>>", widget->name);
	for (int i = 0; i < wc->length; i++) {
		widget_debug_print(wc->widgets[i]);
		if (wc->orientation == VERTICAL)
			printf("\n");
	}
}

static Widget *
container_widget_first(WidgetContainer *wc) {
	wc->current = 0; // TODO make focusing work better
	return wc->widgets[0];
}

static Widget *
container_widget_next(WidgetContainer *wc) {
	wc->current = wc->current + 1;
	return wc->widgets[wc->current];
}

static const WidgetMethods container_base_vtable = {
	.debug_print = container_widget_debug_print
};

static const WidgetContainerMethods container_extra_vtable = {
	.first = container_widget_first,
	.next = container_widget_next,
};

// Public

WidgetContainer *
widget_container_new(const char *name, Orientation orientation, int length, ...) {
	va_list list;

	WidgetContainer *new = malloc(sizeof(WidgetContainer));
	new->base.name = name;
	new->base.type = CONTAINER;
	new->base.vtable = &container_base_vtable;
	new->container_vtable = &container_extra_vtable;
	new->orientation = orientation;

	new->length = length;
	new->widgets = malloc(length * sizeof(Widget *));
	va_start(list, length);
	for (int i = 0; i < length; i++) {
		new->widgets[i] = va_arg(list, Widget *);
	}
	va_end(list);

	return new;
}

inline Widget *
widget_container_first(WidgetContainer *wc) {
	return wc->container_vtable->first(wc);
}

inline Widget *
widget_container_next(WidgetContainer *wc) {
	return wc->container_vtable->next(wc);
}
