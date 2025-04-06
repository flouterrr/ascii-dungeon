#include "gameover.h"


void gameover_init(gameover_t* gameover)
{

}


int gameover_update(gameover_t* gameover, char input)
{
	if (input != '\r' && input != ' ') return 1;

	gameover->stage += 1;

	return 0;
}


void gameover_render(gameover_t* gameover)
{
	display_render_sprite(
		SPRITE_GAMEOVER, 
		DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, true,
		COLOR_RED, COLOR_BLACK
	);
}