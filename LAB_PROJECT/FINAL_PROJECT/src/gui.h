#ifndef GUI_H
#define GUI_H

#include "image.h"
#include "filter.h"
#include <iup.h>

Ihandle* build_main_gui(void);
void cleanup_images(void);

#endif
