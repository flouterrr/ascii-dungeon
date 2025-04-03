#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "utils.h"
#include "battle.h"
#include "overworld.h"


typedef struct {
    int cur_game_state;
    battle_t battle;
    overworld_t overworld;
} game_t;

game_t* get_game(void);

void init_game();
int get_current_game_state();
void start_battle();


#endif // GAME_H
