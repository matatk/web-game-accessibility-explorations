#include <stdlib.h>

#include "page.h"
#include "ui.h"
#include "widgetbutton.h"
#include "widgetcontainer.h"
#include "widgetsubpage.h"

Page *
make_pages() {
	Page *episode_page = new_page(
		widget_container_new("Episode", VERTICAL, 3,
			widget_button_new("Big pile of great dread"),
			widget_button_new("The floors look swell"),
			widget_button_new("Some Pearnod")));

	Page *player_options_page = new_page(
		widget_container_new("Player Options", VERTICAL, 2,
			widget_button_new("Name"),
			widget_button_new("Colour")));

	Page *options_page = new_page(
		widget_container_new("Options", VERTICAL, 5,
			widget_subpage_new("Player", player_options_page),
			widget_button_new("Controls"),
			widget_button_new("Gameplay"),
			widget_button_new("Sound"),
			widget_button_new("Video")));

	Page *main_page = new_page(
		widget_container_new("Main", VERTICAL, 4,
			widget_subpage_new("New game", episode_page),
			widget_subpage_new("Options", options_page),
			widget_container_new("Extra", HORIZONTAL, 2,
				widget_button_new("contained1"),
				widget_button_new("contained2")),
			widget_button_new("Exit")));

	return main_page;
}

int
main() {
	if (ui_init() < 0)
		return -1;
	Page *root = make_pages();
	debug_print_page_tree(root);
	return ui_start(root);
}
