#pragma once
#include "widget.h"

typedef struct WidgetLabel {
	struct Widget;
} WidgetLabel;

WidgetLabel *widget_label_new(const char *);
void widget_label_constructor(WidgetLabel *, const char *);
