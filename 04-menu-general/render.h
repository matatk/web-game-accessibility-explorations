#ifndef _RENDER_H_
#define _RENDER_H_

#include "menu.h"

void render_menu(Menu *, void *);

// Accessibility stuff
void expose_menu(Menu *);
void expose_current_item(Menu *);

#endif
