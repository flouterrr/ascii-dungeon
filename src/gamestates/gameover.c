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


void gameover_render(gameover_t* gameover, HANDLE console_handle)
{

}