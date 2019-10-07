#include <stdlib.h>

#include "menu.h"
#include "ui.h"

Menu *make_menus() {
	Menu *episode_menu = new_menu(3,
		new_menu_item("Big pile of great dread", NULL),
		new_menu_item("The floors look swell", NULL),
		new_menu_item("Some Pearnod", NULL));

	Menu *player_options_menu = new_menu(2,
		new_menu_item("Name", NULL),
		new_menu_item("Colour", NULL));

	Menu *options_menu = new_menu(5,
		new_menu_item("Player", player_options_menu),
		new_menu_item("Controls", NULL),
		new_menu_item("Gameplay", NULL),
		new_menu_item("Sound", NULL),
		new_menu_item("Video", NULL));

	Menu *main_menu = new_menu(3,
		new_menu_item("New game", episode_menu),
		new_menu_item("Options", options_menu),
		new_menu_item("Exit", NULL));

	return main_menu;
}

int main() {
	if (ui_init() < 0) return -1;
	return ui_start(make_menus());
}
