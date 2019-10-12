#include <stdlib.h>

#include "menu.h"
#include "ui.h"
#include "widgetbutton.h"
#include "widgetsubmenu.h"

Menu *make_menus() {
	Menu *episode_menu = new_menu(3,
		new_widget_button("Big pile of great dread"),
		/*
		new_menu(2,
			new_widget_button("moo1"),
			new_widget_button("moo2")),
		*/
		new_widget_button("The floors look swell"),
		new_widget_button("Some Pearnod"));

	Menu *player_options_menu = new_menu(2,
		new_widget_button("Name"),
		new_widget_button("Colour"));

	Menu *options_menu = new_menu(5,
		new_widget_submenu("Player", player_options_menu),
		new_widget_button("Controls"),
		new_widget_button("Gameplay"),
		new_widget_button("Sound"),
		new_widget_button("Video"));

	Menu *main_menu = new_menu(3,
		new_widget_submenu("New game", episode_menu),
		new_widget_submenu("Options", options_menu),
		new_widget_button("Exit"));

	return main_menu;
}

int main() {
	if (ui_init() < 0) return -1;
	Menu *root = make_menus();
	debug_print_menu_tree(root);
	return ui_start(root);
}
