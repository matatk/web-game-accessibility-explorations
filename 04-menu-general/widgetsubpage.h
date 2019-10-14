#pragma once
#include "page.h"
#include "widget.h"

#define AS_WIDGET_SUBPAGE(widget) ((WidgetSubpage *)widget)

typedef struct WidgetSubpage {
	Widget base;
	Page *sub_page;
} WidgetSubpage;

WidgetSubpage *widget_subpage_new(const char *, Page *);
