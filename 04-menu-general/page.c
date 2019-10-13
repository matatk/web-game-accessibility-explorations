#include <stdio.h>
#include <stdlib.h>

#include "page.h"
#include "widgetcontainer.h"

Page *
new_page(Widget *root) {
	Page *new = malloc(sizeof(Page));
	new->parent = NULL;
	new->focused = 0;
	new->root = root;
	return new;
}

void
_debug_print_page_tree(Page *page, int depth) {
	printf("debug:\n");
	widget_debug_print(page->root);
	printf("</debug>\n");
	/*
	for (int d = 0; d < depth; d++)
		printf("\t");
	printf("Page: %p; Parent: %p\n", page, page->parent);

	for (int i = 0; i < page->length; i++) {
		for (int d = 0; d < depth; d++)
			printf("\t");
		Widget *item = page->items[i];
		printf("%d: ", i);
		widget_debug_print(item);
		printf("\n");
		if (widget_is_a(item, SUBPAGE)) {
			_debug_print_page_tree(
				((WidgetSubpage *)item)->sub_page, depth + 1);
		}
	}
	*/
}

void
debug_print_page_tree(Page *page) {
	_debug_print_page_tree(page, 0);
}

void
move_down(Page *page) {
	int desired = page->focused + 1;
	int found_non_container_elements = 0;

	printf("move_down(): page currently focused: %d; desired: %d\n", page->focused, desired);

	WidgetContainer *current_container = NULL;
	Widget *current = page->root;

	do {
		if (widget_is_a(current, CONTAINER)) {
			current_container = (WidgetContainer *)current;
			current = widget_container_first(current_container);
		} else {
			++found_non_container_elements;
			if (found_non_container_elements < desired) {
				current = widget_container_next(current_container);
			}
		}
	} while (found_non_container_elements < desired);

	page->focused = found_non_container_elements;
	printf("current_container name: %s\n", current_container->base.name);
	printf("current name: %s\n", current->name);
	printf("page focused: %d\n", page->focused);
}

void
move_up(Page *page) {
	//
}

Page *
page_activate(Page *page) {
	return page;
	/*
	Widget *current = page->items[page->current];
	if (widget_is_a(current, SUBPAGE)) {
		return ((WidgetSubpage *)current)->sub_page;
	} else {
		return page;
	}
	*/
}

Page *
page_back(Page *page) {
	if (page->parent != NULL) {
		return page->parent;
	} else {
		return page;
	}
}
