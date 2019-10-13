#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widget.h"

bool
widget_is_a(const Widget* widget, WidgetType type) {
	return widget->type == type;
}

inline void
widget_debug_print(const Widget* widget) {
	widget->vtable->debug_print(widget);
}
