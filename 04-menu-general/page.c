#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "page.h"
#include "widgetsubpage.h"

Page *new_page(int length, ...) {
	va_list list;

	Page *new = malloc(sizeof(Page));
	new->parent_page = NULL;
	new->length = length;
	new->current = 0;
	new->items = malloc(length * sizeof(Widget *));

	va_start(list, length);
	for (int i = 0; i < length; i++) {
		new->items[i] = va_arg(list, Widget *);

		if (widget_is_a(new->items[i], SUBPAGE)) {
			((WidgetSubpage *)new->items[i])->sub_page->parent_page = new;
		}
	}
	va_end(list);

	return new;
}

void _debug_print_page_tree(Page *page, int depth) {
	for (int d = 0; d < depth; d++) printf("\t");
	printf("Page: %p; Parent: %p\n", page, page->parent_page);

	for (int i = 0; i < page->length; i++) {
		for (int d = 0; d < depth; d++) printf("\t");
		Widget *item = page->items[i];
		printf("%d: ", i);
		widget_debug_print(item);
		printf("\n");
		if (widget_is_a(item, SUBPAGE)) {
			_debug_print_page_tree(
				((WidgetSubpage *)item)->sub_page, depth + 1);
		}
	}
}

void debug_print_page_tree(Page *page) {
	_debug_print_page_tree(page, 0);
}

void page_down(Page *page) {
	page->current = (page->current + 1) % page->length;
}

void page_up(Page *page) {
	page->current = page->current == 0
		? page->length - 1
		: page->current - 1;
}

Page *page_activate(Page *page) {
	Widget *current = page->items[page->current];
	if (widget_is_a(current, SUBPAGE)) {
		return ((WidgetSubpage *)current)->sub_page;
	} else {
		return page;
	}
}

Page *page_back(Page *page) {
	if (page->parent_page != NULL) {
		return page->parent_page;
	} else {
		return page;
	}
}
