#include <stdlib.h>

#include "page.h"
#include "ui.h"
#include "widget.h"
#include "widgetbutton.h"
#include "widgetcontainer.h"
#include "widgetlabel.h"
#include "widgetslider.h"
#include "widgetsubpage.h"
#include "widgettextbox.h"

Page *
make_pages() {
	Page *episode_page = new_page(
		AS_WIDGET(widget_container_new("Episode", VERTICAL, 3,
			widget_button_new("Big pile of great dread"),
			widget_button_new("The floors look swell"),
			widget_button_new("Some Pearnod"))));

	Page *player_options_page = new_page(
		AS_WIDGET(widget_container_new("Player Options", VERTICAL, 2,
			widget_container_new("HorizPlayerName", HORIZONTAL, 2,
				widget_label_new("Name"),
				widget_text_new("Options.Player.Name")),
			widget_container_new("HorizTeamName", HORIZONTAL, 2,
				widget_label_new("Team"),
				widget_text_new("Options.Player.Team")))));

	Page *sound_options_page = new_page(
		AS_WIDGET(widget_container_new("Sound Options", VERTICAL, 2,
			widget_container_new("HorizSfxVolume", HORIZONTAL, 2,
				widget_label_new("SFX Volume"),
				widget_slider_new("ctrlSfxVolume", 0, 4, 5)),
			widget_container_new("HorizMusicVolume", HORIZONTAL, 2,
				widget_label_new("Music Volume"),
				widget_slider_new("ctrlMusicVolume", 0, 3, 5)))));

	Page *options_page = new_page(
		AS_WIDGET(widget_container_new("Options", VERTICAL, 5,
			widget_subpage_new("Player", player_options_page),
			widget_button_new("Controls"),
			widget_button_new("Gameplay"),
			widget_subpage_new("Sound", sound_options_page),
			widget_button_new("Video"))));

	return new_page(
		AS_WIDGET(widget_container_new("Main Menu", VERTICAL, 4,
			widget_subpage_new("New game", episode_page),
			widget_subpage_new("Options", options_page),
			widget_button_new("Help"),
			widget_button_new("Exit"))));
}

int
main() {
	if (ui_init() < 0) return -1;
	Page *root = make_pages();
	debug_print_page_tree(root);
	return ui_start(root);
}
