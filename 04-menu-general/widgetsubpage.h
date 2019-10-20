#pragma once
#include "page.h"
#include "widget.h"

#define AS_WIDGET_SUBPAGE(widget) (WidgetSubpage *)widget

typedef struct WidgetSubpage {
	struct Widget;
	Page *sub_page; // TODO const?
} WidgetSubpage;

WidgetSubpage *widget_subpage_new(const char *, Page *);
void widget_subpage_constructor(WidgetSubpage *, const char *, Page *);
