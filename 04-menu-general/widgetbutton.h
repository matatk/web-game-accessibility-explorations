#pragma once
#include "widget.h"

typedef struct WidgetButton {
	Widget base;
} WidgetButton;

WidgetButton *widget_button_new(const char *);
