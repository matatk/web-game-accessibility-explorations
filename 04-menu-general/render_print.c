// TODO: Support horizontal contiainers
#include <stdio.h>

#include "page.h"
#include "widget.h"
#include "widgetcontainer.h"

static void
render_widget(Page *page, int depth, Widget *widget) {
	if (widget_is_a(widget, CONTAINER)) {
		WidgetContainer *wc = AS_WIDGET_CONTAINER(widget);
		for (int i = 0; i < depth; i++) printf(" ");
		printf("--- %s ---\n", wc->name);
		for (int i = 0; i < wc->length; i++) {
			render_widget(page, depth + 1, wc->widgets[i]);
		}
	} else {
		for (int i = 0; i < depth; i++) printf(" ");
		printf("%s ", widget == page->focused ? "+" : " ");
		switch (widget->type) {
		case BUTTON:
			printf("[%s]\n", widget->name);
			break;
		case SUBPAGE:
			printf("%s >\n", widget->name);
			break;
		case LABEL:
			printf("%s:\n", widget->name);
			break;
		case TEXTBOX:
			printf("_%s_\n", widget->name);
			break;
		default:
			printf("DEFAULT: %s\n", widget->name);
			break;
		}
	}
}

void
render_page(Page *page, void *unused) {
	Widget *root = page->root;
	render_widget(page, 0, root);
}
