#include <stdio.h>
#include <stdlib.h>

#include "page.h"

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
	printf("move_down(): page currently focused: %d\n", page->focused);
	//page->root->page->current = (page->current + 1) % page->length;
}

void
move_up(Page *page) {
	//
}

Page *
page_activate(Page *page) {
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
