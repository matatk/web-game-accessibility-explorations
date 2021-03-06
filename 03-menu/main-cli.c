#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "menu/menu.h"
#include "render/render.h"

bool is(char input, const char *str) {
	return strncmp(&input, str, 1) == 0;
}

int main() {
	Menu *root = make_menus();
	Menu *current = root;
	bool quit = false;

	debug_print_menu_tree(current);
	printf("\nUse j/k as arrow keys; e to enter; b to go back; q to quit\n");

	while (!quit) {
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
		}
	}

	return 0;
}
