// TODO: support horizontal containers
#include <stdio.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"

// <------------------ total width ------------------>
// | <-- chevron --> <-- initial --> <-- chevron --> |
// | <-- d --> <-- c --> <-- init - de --> <-- c --> |

const int TOTAL_WIDTH = 38;
const int INDICATOR_WIDTH = 3;
const int BORDER_WIDTH = 2;
const int INITIAL_BARE_WIDTH = TOTAL_WIDTH - (2 * BORDER_WIDTH);
const int INITIAL_CONTENT_WIDTH = TOTAL_WIDTH - (2 * INDICATOR_WIDTH) - (2 * BORDER_WIDTH);

const char *CHEVRON = ">>>";
const char *SELECTED = " + ";
const char *EMPTY = "   ";
const char *BORDER_L = "| ";
const char *BORDER_R = " |";

static void
repeat(int times, const char *string) {
	for (int i = 0; i < times; i++) {
		if (string == NULL) {
			printf(" ");
		} else {
			printf("%s", string);
		}
	}
}

static void
padding(int depth, const char *string) {
	repeat(depth, string);
}

static void
render_widget(Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, CONTAINER)) {
		WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
		//
		printf("%s", BORDER_L);
		padding(depth, "-");
		printf("-- %-*s---------------",
			INITIAL_BARE_WIDTH - depth - 18,
			wc->name);
		printf("%s", BORDER_R);
		printf("\n");
		//
		for (int i = 0; i < wc->length; i++) {
			render_widget(page, depth + 1, wc->widgets[i]);
		}
		//
		printf("%s", BORDER_L);
		repeat(INITIAL_BARE_WIDTH, "-");
		printf("%s", BORDER_R);
		printf("\n");
		//
	} else {
		printf("%s", BORDER_L);
		padding(depth, NULL);
		printf("%s", widget == page->focused ? SELECTED : EMPTY);
		switch (widget->type) {
		case BUTTON:
			printf("[%-*s]",
				INITIAL_CONTENT_WIDTH - depth - 2,
				widget->name);
			printf("%s", EMPTY);
			break;
		case SUBPAGE:
			printf("%-*s",
				INITIAL_CONTENT_WIDTH - depth,
				widget->name);
			printf("%s", CHEVRON);
			break;
		case LABEL:
			printf("%-*s:",
				INITIAL_CONTENT_WIDTH - depth - 1,
				widget->name);
			printf("%s", EMPTY);
			break;
		case TEXTBOX:
			printf("___%-*s___",
				INITIAL_CONTENT_WIDTH - depth - 6,
				widget->name);
			printf("%s", EMPTY);
			break;
		default:
			printf("DEFAULT: %s", widget->name);
			break;
		}
		printf("%s", BORDER_R);
		printf("\n");
	}
}

void
render_page(Page *page) {
	printf("----======<<<<<< PAGE >>>>>>======----\n");
	render_widget(page, 0, page->root);
	printf("----======<<<<<<~~~~~~>>>>>>======----\n");
}
