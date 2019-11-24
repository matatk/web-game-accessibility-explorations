#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat

#include "widgetcontainer.h"

typedef enum { // TODO how to make static? or why not needed?
	TOP,
	BOTTOM
} Direction;

static char *
newline_or_space(const WidgetContainer *wc) {
	if (wc->orientation == VERTICAL)
		return "\n";
	return " ";
}

static char *
container_widget_to_string(const Widget *widget, const int depth) {
	WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
	char *start;
	char *all;

	asprintf(&start, "%s<<%d %s %s>>%s",
		widget_padding(depth),
		depth,
		widget->name,
		widget->parent == NULL ? "NP" : "HP",
		newline_or_space(wc));

	int buffer_size = sizeof(char) * 4096 + 1;
	char *buffer = malloc(buffer_size);
	buffer[0] = 0;

	for (int i = 0; i < wc->length; i++) {
		snprintf(
			buffer + strlen(buffer),
			buffer_size - strlen(buffer),
			"%s%s%s",
			wc->orientation == VERTICAL ? widget_padding(depth) : "",
			widget_to_string(
				wc->widgets[i],
				wc->orientation == VERTICAL ? depth : 0),
			i == (wc->length - 1) ? " " : newline_or_space(wc));
	}

	asprintf(&all, "%s%s", start, buffer);
	free(buffer);
	return all;
}

static Widget *
first_non_label(WidgetContainer *wc) {
	int idx = -1;
	Widget *widget = NULL;
	do {
		idx++;
		wc->current = idx;
		widget = wc->widgets[wc->current];
	} while (idx <= wc->length - 1 && widget->type == LABEL);
	// FIXME DRY condition
	return widget;
}

static Widget *
last_non_label(WidgetContainer *wc) {
	int idx = wc->length;
	Widget *widget = NULL;
	do {
		idx--;
		wc->current = idx;
		widget = wc->widgets[wc->current];
	} while (idx >= 0 && widget->type == LABEL);
	// FIXME DRY condition
	return widget;
}

static Widget *
container_widget_first(WidgetContainer *wc) {
	return first_non_label(wc);
}

static Widget *
container_widget_enter(WidgetContainer *wc, Direction dir) {
	switch (dir) {
	case TOP:
		return first_non_label(wc);
	case BOTTOM:
		return last_non_label(wc);
	}
}

static Widget *
direct_or_contained_widget(Widget *widget, const Direction direction) {
	if (widget_is_a(widget, CONTAINER)) {
		return container_widget_enter(AS_WIDGET_CONTAINER(widget), direction);
	}
	return widget;
}

static Widget *
container_widget_next(WidgetContainer *wc) {
	int idx = wc->current + 1;
	Widget *widget = AS_WIDGET(wc);

	// FIXME DRY condition
	while (idx <= wc->length - 1 && wc->widgets[idx]->type == LABEL) {
		idx++;
	}

	if (idx > wc->length - 1) {
		if (widget->parent == NULL) {
			wc->current = 0;
			return direct_or_contained_widget(wc->widgets[wc->current], TOP);
		}
		return container_widget_next(AS_WIDGET_CONTAINER(widget->parent));
	}

	wc->current = idx;
	Widget *next = wc->widgets[wc->current];
	return direct_or_contained_widget(next, TOP);
}

static Widget *
container_widget_previous(WidgetContainer *wc) {
	int idx = wc->current - 1;
	Widget *widget = AS_WIDGET(wc);

	// FIXME DRY condition
	while (idx >= 0 && wc->widgets[idx]->type == LABEL) {
		idx--;
	}

	if (idx < 0) {
		if (widget->parent == NULL) {
			wc->current = wc->length - 1;
			return direct_or_contained_widget(wc->widgets[wc->current], BOTTOM);
		}
		return container_widget_previous(AS_WIDGET_CONTAINER(widget->parent));
	}

	wc->current = idx;
	Widget *prev = wc->widgets[wc->current];
	return direct_or_contained_widget(prev, BOTTOM);
}

static const WidgetMethods container_base_vtable = {
	.to_string = container_widget_to_string
};

static const WidgetContainerMethods container_extra_vtable = {
	.first = container_widget_first,
	.next = container_widget_next,
	.previous = container_widget_previous,
};

// Public

WidgetContainer *
widget_container_new(const char *name, Orientation orientation, int length, ...) {
	WidgetContainer *new = malloc(sizeof(WidgetContainer));

	va_list args;
	va_start(args, length);

	widget_container_constructor(new, name, orientation, length, args);

	va_end(args);

	return new;
}

void
widget_container_constructor(WidgetContainer *new,
	const char *name, Orientation orientation, int length, va_list args) {
	widget_constructor(AS_WIDGET(new), name);
	new->type = CONTAINER;
	new->vtable = &container_base_vtable;

	new->container_vtable = &container_extra_vtable;
	new->orientation = orientation;
	new->length = length;
	new->widgets = malloc(length * sizeof(Widget *));

	for (int i = 0; i < length; i++) {
		Widget *widget = va_arg(args, Widget *);
		widget->parent = AS_WIDGET(new);
		new->widgets[i] = widget;
		if (widget_is_a(widget, CONTAINER)) widget->parent = AS_WIDGET(new);
	}
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
