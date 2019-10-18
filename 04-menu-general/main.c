#include <stdlib.h>

#include "page.h"
#include "ui.h"
#include "widget.h"
#include "widgetbutton.h"
#include "widgetcontainer.h"
#include "widgetlabel.h"
#include "widgetsubpage.h"
#include "widgettextbox.h"

Page *
make_pages() {
	Page *episode_two = new_page(
			widget_new("Episode Two"));

	Page *episode_page = new_page(
		AS_WIDGET(widget_container_new("Episode", VERTICAL, 3,
			widget_button_new("Big pile of great dread"),
			widget_subpage_new("The floors look swell", episode_two),
			widget_button_new("Some Pearnod"))));

	Page *player_options_page = new_page(
		AS_WIDGET(widget_container_new("Player Options", VERTICAL, 2,
			widget_container_new("Player Name", HORIZONTAL, 2,
				widget_label_new("Name"),
				widget_textbox_new("Name")),
			widget_container_new("Team Colour", HORIZONTAL, 2,
				widget_label_new("Colour"),
				widget_textbox_new("Colour")))));

	Page *options_page = new_page(
		AS_WIDGET(widget_container_new("Options", VERTICAL, 5,
			widget_subpage_new("Player", player_options_page),
			widget_button_new("Controls"),
			widget_button_new("Gameplay"),
			widget_button_new("Sound"),
			widget_button_new("Video"))));

	return new_page(
		AS_WIDGET(widget_container_new("Main", VERTICAL, 5,
			widget_subpage_new("New game", episode_page),
			widget_subpage_new("Options", options_page),
			widget_container_new("Extra", HORIZONTAL, 2,
				widget_button_new("contained1"),
				widget_label_new("contained2")),
			widget_new("Help"),
			widget_button_new("Exit"))));
}

int
main() {
	if (ui_init() < 0) return -1;
	Page *root = make_pages();
	debug_print_page_tree(root);
	return ui_start(root);
}
