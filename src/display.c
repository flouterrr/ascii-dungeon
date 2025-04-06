#include "display.h"
#include "console.h"


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


display_cell_t* display_get_cell(int x, int y)
{
	return &s_display.cells[x + (y * DISPLAY_WIDTH)];
}


void display_set_cell(int x, int y, char c, COLOR_T fg_color, COLOR_T bg_color)
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
			display_set_cell(pos_x + x, pos_y + y, sprite_char, fg_color, bg_color);
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
		display_set_cell(pos_x + i, pos_y, str[i], fg_color, bg_color);
	}

	free(str);
}


void display_print()
{
	for (int y = -1; y <= DISPLAY_HEIGHT; y++)
	{
		for (int x = -1; x <= DISPLAY_WIDTH; x++)
		{
			display_cell_t* cell;

			if (y <= -1 || y >= DISPLAY_HEIGHT || x <= -1 || x >= DISPLAY_WIDTH)
			{
				cell = &s_border_cell;
			}
			else
			{
				cell = display_get_cell(x, y);
			}
			console_set_color(cell->fg_color, cell->bg_color);
			printf("%c", cell->c);
			console_reset_color();
		}
		printf("\n");
	}
}