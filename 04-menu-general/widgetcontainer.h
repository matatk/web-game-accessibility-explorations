#ifndef _WIDGETCONTAINER_H_
#define _WIDGETCONTAINER_H_

#include "widget.h"

typedef struct WidgetContainer {
	Widget base;
	int length;
	Widget **widgets;
	int current;
} WidgetContainer;

WidgetContainer *
new_widget_container(const char *, int, ...);

// Private

typedef struct WidgetContainerMethods {
	int (*next)(const WidgetContainer *);
} WidgetContainerMethods;

#endif
