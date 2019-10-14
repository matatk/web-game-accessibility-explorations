#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "widgetcontainer.h"

#define AS_WIDGET_CONTAINER(widget) (WidgetContainer *)widget

typedef enum {
	TOP,
	BOTTOM
} Direction;

static void
container_widget_debug_print(const Widget *widget) {
	WidgetContainer *wc = (WidgetContainer *)widget;
	printf("<<%s %s>>",
		widget->name,
		wc->parent == NULL ? "NP" : "HP");
	for (int i = 0; i < wc->length; i++) {
		widget_debug_print(wc->widgets[i]);
		if (wc->orientation == VERTICAL)
			printf("\n");
	}
}

static Widget *
container_widget_first(WidgetContainer *wc) {
	return wc->widgets[0];
}

static Widget *
container_widget_enter(WidgetContainer *wc, Direction dir) {
	switch (dir) {
	case TOP:
		wc->current = 0;
		return wc->widgets[0];
	case BOTTOM:
		wc->current = wc->length - 1;
		return wc->widgets[wc->current];
	}
}

Widget *
container_widget_next(WidgetContainer *wc) {
	int idx = wc->current + 1;

	if (idx > wc->length - 1) {
		if (wc->parent == NULL) {
			wc->current = 0;
			return wc->widgets[wc->current];
		}
		return container_widget_next(AS_WIDGET_CONTAINER(wc->parent));
	}

	wc->current = idx;
	Widget *next = wc->widgets[wc->current];
	if (widget_is_a(next, CONTAINER)) {
		return container_widget_enter(AS_WIDGET_CONTAINER(next), TOP);
	}
	return wc->widgets[wc->current];
}

Widget *
container_widget_previous(WidgetContainer *wc) {
	int idx = wc->current - 1;

	if (idx < 0) {
		if (wc->parent == NULL) {
			wc->current = wc->length - 1;
			return wc->widgets[wc->current];
		}
		return container_widget_previous(AS_WIDGET_CONTAINER(wc->parent));
	}

	wc->current = idx;
	Widget *prev = wc->widgets[wc->current];
	if (widget_is_a(prev, CONTAINER)) {
		return container_widget_enter(AS_WIDGET_CONTAINER(prev), BOTTOM);
	}
	return wc->widgets[wc->current];
}

static const WidgetMethods container_base_vtable = {
	.debug_print = container_widget_debug_print
};

static const WidgetContainerMethods container_extra_vtable = {
	.first = container_widget_first,
	.next = container_widget_next,
	.previous = container_widget_previous,
};

// Public

WidgetContainer *
widget_container_new(const char *name, Orientation orientation, int length, ...) {
	va_list list;

	WidgetContainer *new = malloc(sizeof(WidgetContainer));
	new->base.name = name;
	new->base.type = CONTAINER;
	new->parent = NULL;
	new->base.vtable = &container_base_vtable;
	new->container_vtable = &container_extra_vtable;
	new->orientation = orientation;

	new->length = length;
	new->widgets = malloc(length * sizeof(Widget *));
	va_start(list, length);
	for (int i = 0; i < length; i++) {
		Widget *widget = va_arg(list, Widget *);
		widget->parent = AS_WIDGET(new);
		new->widgets[i] = widget;
		if (widget_is_a(widget, CONTAINER))
			((WidgetContainer *)widget)->parent = AS_WIDGET(new);
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

inline Widget *
widget_container_previous(WidgetContainer *wc) {
	return wc->container_vtable->previous(wc);
}
