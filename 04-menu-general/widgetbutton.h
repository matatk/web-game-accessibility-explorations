#ifndef _BUTTONWIDGET_H_
#define _BUTTONWIDGET_H_

#include <stdlib.h>

#include "widget.h"

typedef struct WidgetButton {
	Widget base;
} WidgetButton;

WidgetButton *new_widget_button(const char *);

#endif
