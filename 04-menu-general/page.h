#ifndef _PAGE_H_
#define _PAGE_H_

#include "widget.h"

typedef struct Page Page;

// Public

Page *
new_page(Widget *);

void
move_down(Page *);
void
move_up(Page *);
Page *
page_activate(Page *);
Page *
page_back(Page *);

void
debug_print_page_tree(Page *);

// Private

typedef struct Page {
	int focused;
	Widget *root;
	Page *parent;
} Page;

#endif
