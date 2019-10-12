#ifndef _WIDGET_H_
#define _WIDGET_H_

//const int MAX_ITEM_NAME_SIZE = 23;
#define MAX_ITEM_NAME_SIZE 23

typedef const char * klassname;

typedef struct Widget {
	klassname classname;
	char name[MAX_ITEM_NAME_SIZE];
} Widget;


// Private

void _widget_check_copy_name(const char *name, char *destination);

#endif
