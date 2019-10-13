#ifndef _WIDGETSUBPAGE_H_
#define _WIDGETSUBPAGE_H_

#include "widget.h"
#include "page.h"

typedef struct WidgetSubpage {
	Widget base;
	Page *sub_page;
} WidgetSubpage;

WidgetSubpage *new_widget_subpage(const char *, Page *);

#endif
