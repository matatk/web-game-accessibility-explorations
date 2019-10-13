#include <stdlib.h>

#include "page.h"
#include "ui.h"
#include "widgetbutton.h"
#include "widgetcontainer.h"
#include "widgetsubpage.h"

Page *
make_pages() {
	Page *episode_page = new_page(3,
		new_widget_button("Big pile of great dread"),
		new_widget_button("The floors look swell"),
		new_widget_button("Some Pearnod"));

	Page *player_options_page = new_page(2,
		new_widget_button("Name"),
		new_widget_button("Colour"));

	Page *options_page = new_page(5,
		new_widget_subpage("Player", player_options_page),
		new_widget_button("Controls"),
		new_widget_button("Gameplay"),
		new_widget_button("Sound"),
		new_widget_button("Video"));

	Page *main_page = new_page(4,
		new_widget_subpage("New game", episode_page),
		new_widget_subpage("Options", options_page),
		new_widget_container("Container", 2,
			new_widget_button("contained1"),
			new_widget_button("contained2")),
		new_widget_button("Exit"));

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
