#include "menu.h"

int main() {
	Menu *main_menu = make_menus();
	print_menu(main_menu, 0);
	return 0;
}
