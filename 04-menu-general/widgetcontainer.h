#ifndef _WIDGETCONTAINER_H_
#define _WIDGETCONTAINER_H_

#include "widget.h"

#define AS_WIDGET_CONTAINER(widget) (WidgetContainer *)widget

typedef enum Orientation {
	VERTICAL,
	HORIZONTAL
} Orientation;

typedef struct WidgetContainerMethods WidgetContainerMethods;

typedef struct WidgetContainer {
	Widget base;
	const WidgetContainerMethods *container_vtable;
	int length;
	Widget **widgets;
	int current;
	Orientation orientation;
	Widget *parent; // FIXME remove
} WidgetContainer;

WidgetContainer *widget_container_new(const char *, Orientation, int, ...);
Widget *widget_container_first(WidgetContainer *);
Widget *widget_container_next(WidgetContainer *);
Widget *widget_container_previous(WidgetContainer *);

// Private

typedef struct WidgetContainerMethods {
	Widget *(*first)(WidgetContainer *);
	Widget *(*next)(WidgetContainer *);
	Widget *(*previous)(WidgetContainer *);
} WidgetContainerMethods;

#endif
