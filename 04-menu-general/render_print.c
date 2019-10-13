#include <assert.h>
#include <stdio.h>

#include "page.h"
#include "widget.h"

void
render_page(Page *page, void *unused) {
	widget_debug_print(page->root);
}
