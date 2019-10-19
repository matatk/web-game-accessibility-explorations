#pragma once
#include "widget.h"

typedef struct WidgetText {
	struct Widget;
} WidgetText;

WidgetText *widget_text_new(const char *);
void widget_text_constructor(WidgetText *, const char *);
