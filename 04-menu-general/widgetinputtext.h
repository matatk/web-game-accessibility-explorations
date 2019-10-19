#pragma once
//#include "widget.h"
#include "widgetinput.h"

typedef struct WidgetInputText {
	struct Widget;
} WidgetInputText;

WidgetInputText *widget_input_text_new(const char *);
void widget_input_text_constructor(WidgetInputText *, const char *);
