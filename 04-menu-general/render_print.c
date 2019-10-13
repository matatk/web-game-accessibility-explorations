#include <assert.h>
#include <stdio.h>

#include "page.h"
#include "widget.h"

void
render_page(Page* page, void* unused) {
	for (int i = 0; i < page->length; i++) {
		printf(" %s ", i == page->current ? "+" : " ");
		const Widget* current = page->items[i];
		widget_debug_print(current);
		printf("\n");
	}
}
