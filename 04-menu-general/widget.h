#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <stdbool.h>

typedef enum WidgetType {
	BUTTON,
	SUBPAGE,
	CONTAINER
} WidgetType;

typedef struct WidgetMethods WidgetMethods;

typedef struct Widget {
	int type;
	const char *name;
	const WidgetMethods *vtable;
} Widget;

bool
widget_is_a(const Widget *, WidgetType);
void
widget_debug_print(const Widget *);

// Private

typedef struct WidgetMethods {
	void (*debug_print)(const Widget *widget);
} WidgetMethods;

#endif
