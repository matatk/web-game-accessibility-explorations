#pragma once
#include <stdbool.h>

#define AS_WIDGET(derrived) (Widget *)derrived

typedef enum WidgetType {
	BUTTON,
	SUBPAGE,
	CONTAINER
} WidgetType;

typedef struct WidgetMethods WidgetMethods;
typedef struct Widget Widget;

typedef struct Widget {
	WidgetType type;
	const char *name;
	const WidgetMethods *vtable;
	Widget *parent;
} Widget;

bool widget_is_a(const Widget *, WidgetType);
void widget_debug_print(const Widget *);

// Private

typedef struct WidgetMethods {
	void (*debug_print)(const Widget *);
} WidgetMethods;
