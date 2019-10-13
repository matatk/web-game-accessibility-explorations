#ifndef _WIDGETCONTAINER_H_
#define _WIDGETCONTAINER_H_

#include "widget.h"

typedef struct WidgetContainer {
	Widget base;
	int length;
	Widget **widgets;
} WidgetContainer;

WidgetContainer *
new_widget_container(const char *, int, ...);

#endif
