#ifndef _WIDGETBUTTON_H_
#define _WIDGETBUTTON_H_

#include <stdlib.h>

#include "widget.h"

typedef struct WidgetButton {
	Widget base;
} WidgetButton;

WidgetButton *new_widget_button(const char *);

#endif
