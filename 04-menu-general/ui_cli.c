#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "page.h"
#include "render.h"

Page *root;
Page *current;
bool quit = false;

// Private

bool
is(char input, const char *str) {
	return strncmp(&input, str, 1) == 0;
}

void
display_current_page() {
	render_page(current, NULL);
#ifdef __EMSCRIPTEN__
	expose_page(current);
	expose_current_item(current);
#endif
}

void
one_iter() {
	char input;

	render_page(current, NULL);

	scanf(" %c", &input);
	getchar();

	if (is(input, "q")) {
		printf("<Quitting...>\n");
		quit = true;
	} else {
		if (is(input, "j")) {
			printf("<DOWN>\n");
			move_down(current);
		} else if (is(input, "k")) {
			printf("<UP>\n");
			move_up(current);
		} else if (is(input, "e")) {
			printf("<ENTER>\n");
			current = page_activate(current);
		} else if (is(input, "b")) {
			printf("<BACK>\n");
			current = page_back(current);
		} else {
			printf("<unhandled input>\n");
		}
		printf("\n");
	}
}

// Public

int
ui_init() {
	return 0;
}

int
ui_start(Page *page) {
	current = page;

	printf("Use j/k as up/down; e to enter page; b to go back; q to quit\n\n");

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(one_iter, 0, 1);
#else
	while (!quit) {
		one_iter();
	}
#endif

	return 0;
}
