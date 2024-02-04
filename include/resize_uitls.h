#ifndef _RESIZE_UTILS_
#define _RESIZE_UTILS_

#include <curses.h>

void resize(WINDOW * window, volatile __sig_atomic_t * resized_flag);

#endif