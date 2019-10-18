#include <stdio.h>
#include <stdlib.h>

#include "widgetsubpage.h"

static void
subpage_widget_debug_print(const Widget *widget) {
	printf("(%s -> %p)", widget->name, ((WidgetSubpage *)widget)->sub_page);
}

static const WidgetMethods subpage_base_vtable = {
	.debug_print = subpage_widget_debug_print
};

// Public

WidgetSubpage *
widget_subpage_new(const char *name, const Page *sub_page) {
	WidgetSubpage *new = malloc(sizeof(WidgetSubpage));
	widget_subpage_constructor(new, name, sub_page);
	return new;
}

void
widget_subpage_constructor(WidgetSubpage *new, const char *name, const Page *sub_page) {
	widget_constructor(AS_WIDGET(new), name);
	new->type = SUBPAGE;
	new->vtable = &subpage_base_vtable;
	new->sub_page = sub_page;
}
