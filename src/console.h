#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <stdbool.h>

#include "color.h"


#define CONSOLE_CHAR_MODE_ASCII 0
#define CONSOLE_CHAR_MODE_DLINE 1
#define CONSOLE_CHAR_MODE_T unsigned char

#define DEC_LINE_BR			0x6a
#define DEC_LINE_TR			0x6b
#define DEC_LINE_TL			0x6c
#define DEC_LINE_BL			0x6d
#define DEC_LINE_CROSS		0x6e
#define DEC_LINE_H			0x71
#define DEC_LINE_T_RIGHT	0x74
#define DEC_LINE_T_LEFT		0x75
#define DEC_LINE_T_UP		0x76
#define DEC_LINE_T_DOWN		0x77
#define DEC_LINE_V			0x78
#define DEC_LINE_COUNT		11


void console_init();
void console_cleanup();

void console_set_color(COLOR_T fg_color, COLOR_T bg_color);
void console_set_char_mode(CONSOLE_CHAR_MODE_T mode);
void console_reset_color();
void console_write_character(char c, CONSOLE_CHAR_MODE_T mode, COLOR_T fg_color, COLOR_T bg_color);
void console_replace_char(int x, int y, char c, CONSOLE_CHAR_MODE_T mode, COLOR_T fg_color, COLOR_T bg_color);
void console_clear();


#endif // CONSOLE_H