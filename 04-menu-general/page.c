#include <stdio.h>
#include <stdlib.h>

#include "page.h"
#include "widgetcontainer.h"
#include "widgetsubpage.h"

static Widget *
find_first_interactive_widget(Page *page) {
	Widget *current = page->root;
	do {
		if (widget_is_a(current, CONTAINER)) {
			current = widget_container_first(AS_WIDGET_CONTAINER(current));
		} else {
			return current;
		}
	} while (1);
}

Page *
new_page(Widget *root) {
	Page *new = malloc(sizeof(Page));
	new->parent = NULL;
	new->root = root;
	new->focused = find_first_interactive_widget(new);
	return new;
}

const char *
_debug_print_page_tree(Page *page, int depth) {
	char *string;
	asprintf(&string,
		"%s--- page debug info: ---\n"
		"%sDepth: %d\n"
		"%sFocused: %s\n"
		"%sRoot: %s\n"
		"%sParent: %p\n"
		"%s\n"
		"%s/// page debug info: ///",
		widget_padding(depth),
		widget_padding(depth), depth,
		widget_padding(depth), page->focused->name,
		widget_padding(depth), page->root->name,
		widget_padding(depth), page->parent,
		widget_to_string(page->root, depth),
		widget_padding(depth));
	return string;
}

void
debug_print_page_tree(Page *page) {
	printf("%s\n", _debug_print_page_tree(page, 0));
}

static void
move(Page *page, Widget *(*func)()) {
	Widget *current = page->focused;
	printf("Current focused widget: %s\n", page->focused->name);
	WidgetContainer *current_container = AS_WIDGET_CONTAINER(current->parent);
	if (widget_is_a(AS_WIDGET(current_container), CONTAINER)) {
		page->focused = func(current_container);
	} else {
		printf("ERROR!\n");
	}
	printf("New focused widget: %s\n", page->focused->name);
}

void
move_down(Page *page) {
	move(page, widget_container_next);
}

void
move_up(Page *page) {
	move(page, widget_container_previous);
}

Page *
page_activate(Page *page) {
	Widget *current = page->focused;
	if (widget_is_a(current, SUBPAGE)) {
		return AS_WIDGET_SUBPAGE(current)->sub_page;
	}
	return page;
}

Page *
page_back(Page *page) {
	if (page->parent == NULL) {
		return page;
	}
	return page->parent;
}
