#ifndef DISPLAY_H
#define DISPLAY_H

#include <Windows.h>
#include <stdbool.h>
#include <stdarg.h>

#include "database.h"
#include "utils.h"
#include "color.h"


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
	COLOR_T fg_color;
	COLOR_T bg_color;
	bool dec_line;
} display_cell_t;


typedef struct {
	display_cell_t cells[DISPLAY_SIZE];
	display_cell_t displayed_cells[DISPLAY_SIZE];
} display_t;


void display_init();
void display_set_cell(int x, int y, char c, COLOR_T fg_color, COLOR_T bg_color, bool dec_line);
void display_clear();
void display_render_sprite(int sprite_id, int pos_x, int pos_y, bool origin_center, COLOR_T fg_color, COLOR_T bg_color);
void display_render_text(int pos_x, int pos_y, bool origin_center, COLOR_T fg_color, COLOR_T bg_color, const char* text, ...);
void display_render_box(int pos_x, int pos_y, bool origin_center, int width, int height, bool fill, COLOR_T fg_color, COLOR_T bg_color);
void display_refresh();
void display_draw_border();


#endif // DISPLAY_H