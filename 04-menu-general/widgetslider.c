#include <stdio.h>
#include <stdlib.h>

#include "widgetslider.h"

static char *
slider_widget_to_string(const Widget *widget, const int depth) {
	WidgetSlider *slider = AS_WIDGET_SLIDER(widget);
	char *string;
	asprintf(&string, "%s[%s (%d, %d, %d)]", widget_padding(depth), widget->name,
		slider->value_min, slider->value, slider->value_max);
	return string;
}

static const WidgetMethods slider_base_vtable = {
	.to_string = slider_widget_to_string
};

// Public

WidgetSlider *
widget_slider_new(const char *name, int min, int start, int max) {
	WidgetSlider *new = malloc(sizeof(WidgetSlider));
	widget_slider_constructor(new, name, min, start, max);
	return new;
}

void
widget_slider_constructor(WidgetSlider *new, const char *name, int min, int start, int max) {
	widget_constructor(AS_WIDGET(new), name);
	new->type	   = SLIDER;
	new->vtable	   = &slider_base_vtable;
	new->value_min = min;
	new->value	   = start;
	new->value_max = max;
}
