#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <Windows.h>

#include "database.h"
#include "display.h"


typedef struct {
	int stage;
} gameover_t;

void gameover_init(gameover_t* gameover);
int gameover_update(gameover_t* gameover, char input);
void gameover_render(gameover_t* gameover);


#endif // !GAMEOVER_H
