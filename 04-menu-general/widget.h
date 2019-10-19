#pragma once
#include <stdbool.h>

#define AS_WIDGET(derrived) (Widget *)derrived

typedef enum WidgetType {
	WIDGET,     // Base type; doesn't do much :-)
	BUTTON,
	SUBPAGE,
	CONTAINER,
	LABEL,
	INPUT,      // Base input type; don't use
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
char *widget_debug_print(const Widget *, const int);  // TODO make const

// Intended for widgets only

const char *widget_padding(int);

// Private

typedef struct WidgetMethods {
	char *(*debug_print)(const Widget *, const int);
} WidgetMethods;
