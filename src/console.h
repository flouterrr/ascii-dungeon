#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <stdbool.h>

#include "color.h"


void console_init();
void console_cleanup();

void console_set_color(COLOR_T fg_color, COLOR_T bg_color);
void console_reset_color();


#endif // CONSOLE_H