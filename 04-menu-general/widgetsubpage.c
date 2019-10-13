#include <stdio.h>
#include <stdlib.h>

#include "widgetsubpage.h"

void
subpage_widget_debug_print(const Widget *widget) {
	printf("%s -> %p", widget->name, ((WidgetSubpage *)widget)->sub_page);
}

static const WidgetMethods subpage_vtable = {
	.debug_print = subpage_widget_debug_print
};

WidgetSubpage *
new_widget_subpage(const char *name, Page *sub_page) {
	WidgetSubpage *new = malloc(sizeof(WidgetSubpage));
	new->base.name = name;
	new->base.type = SUBPAGE;
	new->base.vtable = &subpage_vtable;
	new->sub_page = sub_page;
	return new;
}
