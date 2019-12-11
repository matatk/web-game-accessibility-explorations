#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widgettextbox.h"

static char *
text_widget_to_string(const Widget *widget, const int depth) {
	char *string;
	asprintf(&string, "%s[__%s__]", widget_padding(depth), widget->name);
	return string;
}

static char *
text_widget_get(WidgetText *textbox) {
	return textbox->value;
}

static void
text_widget_add(WidgetText *textbox, char input) {
	int length = strlen(textbox->value);
	if (length < MAX_TEXTBOX_VALUE_LENGTH) {
		textbox->value[length] = input;
	}
}

static void
text_widget_del(WidgetText *textbox) {
	int length = strlen(textbox->value);
	textbox->value[length - 1] = '\0';
}

static const WidgetMethods text_base_vtable = {
	.to_string = text_widget_to_string
};

static const WidgetTextMethods text_extra_vtable = {
	.get = text_widget_get,
	.add = text_widget_add,
	.del = text_widget_del
};

// Public

WidgetText *
widget_text_new(const char *name) {
	WidgetText *new = malloc(sizeof(WidgetText));
	widget_text_constructor(new, name);
	return new;
}

void
widget_text_constructor(WidgetText *new, const char *name) {
	widget_constructor(AS_WIDGET(new), name);
	new->type = TEXTBOX;
	new->vtable = &text_base_vtable;

	new->text_vtable = &text_extra_vtable;
}

char *
widget_text_get(WidgetText *textbox) {
	return textbox->text_vtable->get(textbox);
}

void
widget_text_add(WidgetText *textbox, char input) {
	textbox->text_vtable->add(textbox, input);
}

void
widget_text_del(WidgetText *textbox) {
	textbox->text_vtable->del(textbox);
}
