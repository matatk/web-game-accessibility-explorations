#pragma once
#include "widget.h"

typedef struct WidgetTextbox {
	struct Widget;
} WidgetTextbox;

WidgetTextbox *widget_textbox_new(const char *);
void widget_textbox_constructor(WidgetTextbox *, const char *);
