#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "widget.h"

bool widget_is_a(Widget *widget, WidgetType type) {
	return widget->type == type;
}

inline void widget_debug_print(Widget *widget) {
	widget->methods->debug_print(widget);
}

// Internal

void widget_check_copy_name(const char *name, char *destination) {
	size_t name_len = strnlen(name, MAX_ITEM_NAME_SIZE);
	if (name_len > MAX_ITEM_NAME_SIZE) {
		printf("Warning: menu item '%s' is too long (>=%d); truncating.\n",
			name, MAX_ITEM_NAME_SIZE);
		// TODO return nowt, or something with error?
	}
	strncpy(destination, name, MAX_ITEM_NAME_SIZE);
}
