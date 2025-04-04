#ifndef DISPLAY_H
#define DISPLAY_H

#include <Windows.h>
#include <stdbool.h>
#include <stdarg.h>

#include "database.h"
#include "utils.h"


#define DISPLAY_WIDTH 96
#define DISPLAY_HEIGHT 24
#define DISPLAY_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)


enum ENUM_DISPLAY_ORIGIN_TYPE {
	DISPLAY_ORIGIN_TOP_LEFT,
	DISPLAY_ORIGIN_CENTER,
	NUM_DISPLAY_ORIGIN_TYPES
};


typedef struct {
	char c;
	int fg_color;
	int bg_color;
} display_cell_t;


typedef struct {
	display_cell_t cells[DISPLAY_SIZE];
	//HANDLE console_handle;
} display_t;


void display_init();
void display_set_cell(int x, int y, char c, int fg_color, int bg_color);
void display_clear();
void display_render_sprite(int sprite_id, int pos_x, int pos_y, bool origin_center, int fg_color, int bg_color);
void display_render_text(int pos_x, int pos_y, bool origin_center, int fg_color, int bg_color, const char* text, ...);
void display_print(HANDLE console_handle);


#endif // DISPLAY_H