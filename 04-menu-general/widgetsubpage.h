#ifndef _WIDGETSUBPAGE_H_
#define _WIDGETSUBPAGE_H_

#include "page.h"
#include "widget.h"

typedef struct WidgetSubpage {
	Widget base;
	Page *sub_page;
} WidgetSubpage;

WidgetSubpage *
widget_subpage_new(const char *, Page *);

#endif
