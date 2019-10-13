#ifndef _PAGE_H_
#define _PAGE_H_

#include "widget.h"

typedef struct Page Page;

// Public

Page* new_page(int, ...);

void page_down(Page*);
void page_up(Page*);
Page* page_activate(Page*);
Page* page_back(Page*);

void debug_print_page_tree(Page*);

// Private

typedef struct Page {
	int length;
	int current;
	Widget** items;
	Page* parent_page;
} Page;

#endif
