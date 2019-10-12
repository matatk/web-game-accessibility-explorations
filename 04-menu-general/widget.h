#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <stdbool.h>

//const int MAX_ITEM_NAME_SIZE = 23;
#define MAX_ITEM_NAME_SIZE 23

typedef enum WidgetType {
	WIDGET,
	BUTTON,
	SUBMENU
} WidgetType;

typedef struct WidgetMethods WidgetMethods;

typedef struct Widget {
	int type;
	char name[MAX_ITEM_NAME_SIZE];
	WidgetMethods *methods;
} Widget;

bool widget_is_a(Widget *, WidgetType);
void widget_debug_print(Widget *);


// Private

typedef struct WidgetMethods {
	void (*debug_print)(Widget *widget);
} WidgetMethods;

void widget_check_copy_name(const char *, char *);

#endif
