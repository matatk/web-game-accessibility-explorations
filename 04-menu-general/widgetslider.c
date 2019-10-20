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

static void
slider_widget_increase(WidgetSlider *slider) {
	slider->value = slider->value == slider->value_max
		? slider->value_max
		: slider->value + 1;
}

static void
slider_widget_decrease(WidgetSlider *slider) {
	slider->value = slider->value == 0 ? 0 : slider->value - 1;
}

static const WidgetMethods slider_base_vtable = {
	.to_string = slider_widget_to_string
};

static const WidgetSliderMethods slider_extra_vtable = {
	.increase = slider_widget_increase,
	.decrease = slider_widget_decrease
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
	new->type = SLIDER;
	new->vtable = &slider_base_vtable;

	new->slider_vtable = &slider_extra_vtable;
	new->value_min = min;
	new->value = start;
	new->value_max = max;
}

inline void
widget_slider_increase(WidgetSlider *slider) {
	slider->slider_vtable->increase(slider);
}

inline void
widget_slider_decrease(WidgetSlider *slider) {
	slider->slider_vtable->decrease(slider);
}
