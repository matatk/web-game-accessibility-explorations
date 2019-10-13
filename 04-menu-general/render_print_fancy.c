#include <stdio.h>

#include "page.h"
#include "widget.h"

void
render_page(Page* page) {
	printf("----======<<<<<< PAGE >>>>>>======----\n");
	for (int i = 0; i < page->length; i++) {
		Widget* item = page->items[i];
		printf("|   %s %-24s %-3s   |\n",
			i == page->current ? "+" : " ",
			item->name,
			widget_is_a(item, SUBPAGE) ? ">>>" : "");
	}
	printf("----======<<<<<<~~~~~~>>>>>>======----\n");
}
