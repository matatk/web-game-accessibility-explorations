#pragma once
#include <stdbool.h>

#define AS_WIDGET(derrived) (Widget *)derrived

typedef enum WidgetType {
	WIDGET,  // don't use
	BUTTON,
	SUBPAGE,
	CONTAINER,
	LABEL,
	TEXTBOX
} WidgetType;

typedef struct WidgetMethods WidgetMethods;
typedef struct Widget Widget;

typedef struct Widget {
	WidgetType type;
	const char *name;
	const WidgetMethods *vtable;
	Widget *parent;
} Widget;

Widget *widget_new(const char *);
void widget_constructor(Widget *, const char *);

bool widget_is_a(const Widget *, WidgetType);
void widget_debug_print(const Widget *);

// Private

typedef struct WidgetMethods {
	void (*debug_print)(const Widget *);
} WidgetMethods;
