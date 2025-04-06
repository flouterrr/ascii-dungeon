#include "color.h"


color_t color_create(unsigned char code, bool bright)
{
	color_t col = {
		.code = code,
		.bright = bright
	};
	return col;
}