#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "utils.h"
#include "display.h"
#include "gamestates/battle.h"
#include "gamestates/overworld.h"
#include "gamestates/gameover.h"


typedef struct {
    int cur_game_state;
    battle_t battle;
    overworld_t overworld;
    gameover_t gameover;
} game_t;

game_t* get_game(void);

void game_init();
void game_run();
int get_current_game_state();
void start_battle();


#endif // GAME_H
