#include "display.h"

#include "console.h"
#include "utils.h"



static display_t s_display;

static display_cell_t s_border_cell = {
	.c = ':',
	.fg_color = COLOR_WHITE,
	.bg_color = COLOR_BLACK,
};


void display_init()
{
	display_clear();
}


void display_draw_border()
{
	COLOR_T fg = COLOR_WHITE;
	COLOR_T bg = COLOR_BLACK;

	for (int y = 0; y < DISPLAY_HEIGHT + 2; y += DISPLAY_HEIGHT + 1)
	{
		for (int x = 0; x < DISPLAY_WIDTH + 2; x++)
		{
			console_replace_char(x, y, DEC_LINE_H, CONSOLE_CHAR_MODE_DLINE, fg, bg);
		}
	}

	for (int x = 0; x < DISPLAY_WIDTH + 2; x += DISPLAY_WIDTH + 1)
	{
		for (int y = 0; y < DISPLAY_HEIGHT + 2; y++)
		{
			console_replace_char(x, y, DEC_LINE_V, CONSOLE_CHAR_MODE_DLINE, fg, bg);
		}
	}

	// corners
	console_replace_char(
		0, 0,					
		DEC_LINE_TL, CONSOLE_CHAR_MODE_DLINE, fg, bg
	);
	console_replace_char(
		DISPLAY_WIDTH + 1, 0,
		DEC_LINE_TR, CONSOLE_CHAR_MODE_DLINE, fg, bg
	);
	console_replace_char(
		0, DISPLAY_HEIGHT + 1, 
		DEC_LINE_BL, CONSOLE_CHAR_MODE_DLINE, fg, bg
	);
	console_replace_char(
		DISPLAY_WIDTH + 1, DISPLAY_HEIGHT + 1,
		DEC_LINE_BR, CONSOLE_CHAR_MODE_DLINE, fg, bg
	);
}


display_cell_t* display_get_cell(int x, int y)
{
	return &s_display.cells[x + (y * DISPLAY_WIDTH)];
}


void display_set_cell(int x, int y, char c, COLOR_T fg_color, COLOR_T bg_color, bool dec_line)
{
	display_cell_t* cell = display_get_cell(x, y);
	if (c == '\n' || c == EOF || c == '\r' || c == '\0')
	{
		cell->c = ' ';
	}
	else
	{
		cell->c = c;
	}
	cell->fg_color = fg_color;
	cell->bg_color = bg_color;
	cell->dec_line = dec_line;
}


void display_clear()
{
	for (int i = 0; i < DISPLAY_SIZE; i++)
	{
		display_cell_t* cell = &s_display.cells[i];
		cell->c = ' ';
		cell->fg_color = COLOR_WHITE;
		cell->bg_color = COLOR_BLACK;
	}
}


void display_render_sprite(int sprite_id, int pos_x, int pos_y, bool origin_center, COLOR_T fg_color, COLOR_T bg_color)
{
	sprite_t* sprite = get_sprite(sprite_id);

	if (origin_center)
	{
		pos_x -= sprite->width / 2;
		pos_y -= sprite->height / 2;
	}

	for (int y = 0; y < sprite->height; y++)
	{
		if (pos_y + y < 0) continue;
		if (pos_y + y >= DISPLAY_HEIGHT) break;
		for (int x = 0; x < sprite->width; x++)
		{
			if (pos_x + x < 0) continue;
			if (pos_x + x >= DISPLAY_WIDTH) break;
			char sprite_char = sprite->data[x + (y * (sprite->width + 1))];
			display_set_cell(pos_x + x, pos_y + y, sprite_char, fg_color, bg_color, false);
		}
	}
}


void display_render_text(int pos_x, int pos_y, bool origin_center, COLOR_T fg_color, COLOR_T bg_color, const char* text, ...)
{
	va_list va_args;
	va_start(va_args, text);

	int length = vsnprintf(NULL, 0, text, va_args);
	size_t str_size = sizeof(char) * (length + 1);
	char* str = malloc(str_size);
	if (str == NULL)
	{
		printf("Failed to allocate string buffer.\n");
		va_end(va_args);
		return;
	}
	vsnprintf(str, str_size, text, va_args);
	va_end(va_args);

	int str_len = strlen(str);

	if (origin_center)
	{
		pos_x -= str_len / 2;
	}

	if (pos_y >= DISPLAY_HEIGHT) return;

	for (int i = 0; i < str_len; i++)
	{
		if (pos_x + i >= DISPLAY_WIDTH) break;
		display_set_cell(pos_x + i, pos_y, str[i], fg_color, bg_color, false);
	}

	free(str);
}


void display_render_box(int pos_x, int pos_y, bool origin_center, int width, int height, bool fill, COLOR_T fg_color, COLOR_T bg_color)
{
	if (width < 2 || height < 2) return;

	if (origin_center)
	{
		pos_x -= width / 2;
		pos_y -= height / 2;
	}

	/*
			4---1---7
			|       |
			3   0   6
			|       |
			5---2---8
	*/
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char c = '\0';
			int lines = 0;
			unsigned char b_fill = 0;

			if (y == 0)
				lines += 1;
			else if (y == height - 1)
				lines += 2;
			if (x == 0)
				lines += 3;
			else if (x == width - 1)
				lines += 6;

			switch (lines)
			{
			case 0:
				if (fill) c = ' ';
				break;
			case 1:
				if (fill) b_fill = 0b00000100;
				c = DEC_LINE_H;
				break;
			case 2:
				if (fill) b_fill = 0b00000001;
				c = DEC_LINE_H;
				break;
			case 3:
				if (fill) b_fill = 0b00000010;
				c = DEC_LINE_V;
				break;
			case 6:
				if (fill) b_fill = 0b00001000;
				c = DEC_LINE_V;
				break;
			case 4:
				c = DEC_LINE_TL;
				break;
			case 5:
				c = DEC_LINE_BL;
				break;
			case 7:
				c = DEC_LINE_TR;
				break;
			case 8:
				c = DEC_LINE_BR;
				break;
			}

			if (c != ' ')
			{
				unsigned char b_lines = dec_line_char_to_line_bits(c);
				unsigned char b_exlines = 0;
				display_cell_t* cell_at_this_pos = display_get_cell(pos_x + x, pos_y + y);
				if (cell_at_this_pos->dec_line)
					b_exlines = dec_line_char_to_line_bits(cell_at_this_pos->c);

				c = line_bits_to_dec_line_char((b_lines | b_exlines) & ~b_fill);
			}

			if (c != '\0')
			{
				display_set_cell(pos_x + x, pos_y + y, c, fg_color, bg_color, true);
			}
		}
	}
}


void display_refresh()
{
	for (int y = 0; y < DISPLAY_HEIGHT; y++)
	{
		for (int x = 0; x < DISPLAY_WIDTH; x++)
		{
			display_cell_t* cell = display_get_cell(x, y);
			display_cell_t* d_cell = &s_display.displayed_cells[x + (y * DISPLAY_WIDTH)];

			if (d_cell->c != cell->c || d_cell->fg_color != cell->fg_color || d_cell->bg_color != cell->bg_color || d_cell->dec_line != cell->dec_line)
			{
				console_replace_char(x + 1, y + 1, cell->c, cell->dec_line ? CONSOLE_CHAR_MODE_DLINE : CONSOLE_CHAR_MODE_ASCII, cell->fg_color, cell->bg_color);
				d_cell->c = cell->c;
				d_cell->fg_color = cell->fg_color;
				d_cell->bg_color = cell->bg_color;
				d_cell->dec_line = cell->dec_line;
			}
		}
	}

	//console_replace_char(2, 2, 'G', CONSOLE_CHAR_MODE_ASCII, COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
}