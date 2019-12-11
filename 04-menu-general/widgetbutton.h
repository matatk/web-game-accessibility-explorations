#pragma once
#include "widget.h"

typedef struct WidgetButton {
	struct Widget;
} WidgetButton;

WidgetButton *widget_button_new(const char *);
void widget_button_constructor(WidgetButton *, const char *);
