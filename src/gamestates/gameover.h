#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <Windows.h>


typedef struct {
	int stage;
} gameover_t;

void gameover_init(gameover_t* gameover);
int gameover_update(gameover_t* gameover, char input);
void gameover_render(gameover_t* gameover, HANDLE console_handle);


#endif // !GAMEOVER_H
