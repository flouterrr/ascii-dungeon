#include "game.h"


static game_t s_game;

game_t* get_game()
{
    return &s_game;
}

void init_game()
{
    srand(time(NULL));
    s_game.cur_game_state = GAME_STATE_OVERWORLD;
}


int get_current_game_state()
{
    return s_game.cur_game_state;
}


void start_battle()
{
    battle_init(&s_game.battle, randint(NUM_ENEMIES));
    s_game.cur_game_state = GAME_STATE_BATTLE;
}
