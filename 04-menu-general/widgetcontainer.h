#ifndef _WIDGETCONTAINER_H_
#define _WIDGETCONTAINER_H_

#include "widget.h"

typedef enum Orientation {
	VERTICAL,
	HORIZONTAL
} Orientation;

// FIXME make private
typedef enum {
	TOP,
	BOTTOM
} Direction;

typedef struct WidgetContainerMethods WidgetContainerMethods;

typedef struct WidgetContainer {
	Widget base;
	WidgetContainerMethods *container_vtable;
	int length;
	Widget **widgets;
	int current;
	Orientation orientation;
	Widget *parent;
} WidgetContainer;

WidgetContainer *widget_container_new(const char *, Orientation, int, ...);
Widget *widget_container_first(WidgetContainer *);
Widget *widget_container_enter(WidgetContainer *, Direction); // FIXME private!
Widget *widget_container_next(WidgetContainer *);
Widget *widget_container_previous(WidgetContainer *);

// Private

typedef struct WidgetContainerMethods {
	Widget *(*first)(WidgetContainer *);
	Widget *(*current)(WidgetContainer *, Direction);
	Widget *(*next)(WidgetContainer *);
	Widget *(*previous)(WidgetContainer *);
} WidgetContainerMethods;

#endif
