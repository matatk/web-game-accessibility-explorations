#pragma once
#include "widget.h"

typedef struct Page Page;

// Public

Page *new_page(Widget *);

void move_down(Page *);
void move_up(Page *);
Page *page_activate(Page *);
Page *page_back(Page *);

void debug_print_page_tree(Page *);
const char *_debug_print_page_tree(Page *, int);

// Private

typedef struct Page {
	Widget *focused;
	Widget *root;
	Page *parent;
} Page;
