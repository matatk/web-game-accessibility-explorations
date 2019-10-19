#pragma once
#include "widget.h"

#define AS_WIDGET_SLIDER(widget) ((WidgetSlider *)widget)

typedef struct WidgetSliderMethods WidgetSliderMethods;

typedef struct WidgetSlider {
	struct Widget;
	WidgetSliderMethods *slider_vtable;
	int value_min;
	int value;
	int value_max;
} WidgetSlider;

WidgetSlider *widget_slider_new(const char *, int, int, int);
void widget_slider_constructor(WidgetSlider *, const char *, int, int, int);
void widget_slider_increase(WidgetSlider *);
void widget_slider_decrease(WidgetSlider *);

// Private

typedef struct WidgetSliderMethods {
	void (*increase)(WidgetSlider *);
	void (*decrease)(WidgetSlider *);
} WidgetSliderMethods;
