#pragma once
#include "widget.h"

#define AS_WIDGET_TEXTBOX(widget) (WidgetText *)widget

#define MAX_TEXTBOX_VALUE_LENGTH 42

typedef struct WidgetTextMethods WidgetTextMethods;

typedef struct WidgetText {
	struct Widget;
	const WidgetTextMethods *text_vtable;
	char value[MAX_TEXTBOX_VALUE_LENGTH];  // TODO make more stringy
} WidgetText;

WidgetText *widget_text_new(const char *);
void widget_text_constructor(WidgetText *, const char *);
char *widget_text_get(WidgetText *);
void widget_text_add(WidgetText *, char);
void widget_text_del(WidgetText *);

// Private

typedef struct WidgetTextMethods {
	char *(*get)(WidgetText *);
	void (*add)(WidgetText *, char);
	void (*del)(WidgetText *);
} WidgetTextMethods;
