#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "menu.h"

bool is(char input, const char *str) {
	return strncmp(&input, str, 1) == 0;
}

int main() {
	Menu *root = make_menus();
	Menu *current = root;
	bool quit = false;

	print_menu_tree(current);
	printf("\nUse j/k as arrow keys; e to enter; q to quit\n");

	print_menu(current);
	while (!quit) {
		char input;
		scanf(" %c", &input);
		getchar();

		if (is(input, "q")) {
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
			} else {
				printf("<unhandled input>\n");
			}
			print_menu(current);
		}
	}

	return 0;
}
