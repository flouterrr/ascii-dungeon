#include "game.h"


void init_game()
{
    srand(time(NULL));
    g_game.cur_game_state = GAME_STATE_OVERWORLD;
}


int get_current_game_state()
{
    return g_game.cur_game_state;
}


void start_battle()
{
    battle_init(&g_game.battle, randint(NUM_ENEMIES));
    g_game.cur_game_state = GAME_STATE_BATTLE;
}
