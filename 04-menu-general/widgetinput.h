#pragma once
#include "widget.h"

#define AS_WIDGET_INPUT(widget) (WidgetInput *)widget

typedef struct WidgetInput {
	struct Widget;
} WidgetInput;

WidgetInput *widget_input_new(const char *);
void widget_input_constructor(WidgetInput *, const char *);
