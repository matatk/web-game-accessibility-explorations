#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <stdbool.h>

typedef enum WidgetType {
	WIDGET,  // unused
	BUTTON,
	SUBMENU
} WidgetType;

typedef struct WidgetMethods WidgetMethods;

typedef struct Widget {
	int type;
	const char *name;
	WidgetMethods *methods;
} Widget;

bool widget_is_a(const Widget *, WidgetType);
void widget_debug_print(const Widget *);


// Private

typedef struct WidgetMethods {
	void (*debug_print)(const Widget *widget);
} WidgetMethods;

void widget_check_copy_name(const char *, char *);

#endif
