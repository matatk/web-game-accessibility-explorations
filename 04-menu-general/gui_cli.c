#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "menu.h"
#include "render.h"

bool is(char, const char*);

Menu *root;
Menu *current;
bool quit = false;

int init() {
	return 0;
}

void display_current_menu() {
	render_menu(current, NULL);
#ifdef __EMSCRIPTEN__
	expose_menu(current);
	expose_current_item(current);
#endif
}

bool is(char input, const char *str) {
	return strncmp(&input, str, 1) == 0;
}

void one_iter() {
	char input;

	render_menu(current, NULL);

	scanf(" %c", &input);
	getchar();

	if (is(input, "q")) {
		printf("<Quitting...>\n");
		quit = true;
	} else {
		if (is(input, "j")) {
			printf("<DOWN>\n");
			menu_down(current);
		} else if (is(input, "k")) {
			printf("<UP>\n");
			menu_up(current);
		} else if (is(input, "e")) {
			printf("<ENTER>\n");
			current = menu_activate(current);
		} else if (is(input, "b")) {
			printf("<BACK>\n");
			current = menu_back(current);
		} else {
			printf("<unhandled input>\n");
		}
		printf("\n");
	}
}

int start(Menu *menu) {
	current = menu;

	printf("Use j/k as up/down; e to enter menu; b to go back; q to quit\n\n");

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(one_iter, 0, 1);
#else
	while(!quit) {
		one_iter();
	}
#endif

	return 0;
}
