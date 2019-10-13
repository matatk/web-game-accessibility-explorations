#ifndef _WIDGETBUTTON_H_
#define _WIDGETBUTTON_H_

#include "widget.h"

typedef struct WidgetButton {
	Widget base;
} WidgetButton;

WidgetButton *widget_button_new(const char *);

#endif
