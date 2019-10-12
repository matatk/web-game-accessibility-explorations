#ifndef _BUTTONWIDGET_H_
#define _BUTTONWIDGET_H_

#include <stdlib.h>

#include "widget.h"

typedef struct ButtonWidget {
	Widget base;
} ButtonWidget;

ButtonWidget *new_widget_button(const char *);

#endif
