#include <stdio.h>
#include <stdlib.h>

#include "widgetsubpage.h"

static char *
subpage_widget_debug_print(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s(%s -> %p)\n%s%s",
			padding(depth),
			widget->name,
			AS_WIDGET_SUBPAGE(widget)->sub_page,
			padding(depth),
			_debug_print_page_tree(AS_WIDGET_SUBPAGE(widget)->sub_page, depth + 1));
	return string;
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
