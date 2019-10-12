#ifndef _WIDGET_H_
#define _WIDGET_H_

//const int MAX_ITEM_NAME_SIZE = 23;
#define MAX_ITEM_NAME_SIZE 23

typedef struct WidgetMethods WidgetMethods;

typedef struct Widget {
	const char *classname;
	char name[MAX_ITEM_NAME_SIZE];
	WidgetMethods *methods;
} Widget;

void widget_to_string(Widget *);


// Private

typedef struct WidgetMethods {
	void (*to_string)(Widget *widget);
} WidgetMethods;

void _widget_check_copy_name(const char *, char *);

#endif
