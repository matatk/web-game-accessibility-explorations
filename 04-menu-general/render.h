#ifndef _RENDER_H_
#define _RENDER_H_

#include "page.h"

void render_page(Page *, void *);

// Accessibility stuff
void expose_page(Page *);
void expose_current_item(Page *);

#endif
