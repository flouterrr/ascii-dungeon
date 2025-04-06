#include "game.h"


static game_t s_game;


game_t* get_game()
{
    return &s_game;
}


void game_init()
{
    srand(time(NULL));
    s_game.cur_game_state = GAME_STATE_OVERWORLD;

    scene_t* scene_ptr = &s_game.overworld.scene;

    scene_clear(scene_ptr);

    scene_make_room(scene_ptr, 1, 1, 12, 8);
    scene_make_room(scene_ptr, 17, 15, 18, 6);
    scene_make_room(scene_ptr, 28, 5, 10, 8);
    scene_make_room(scene_ptr, 3, 10, 12, 10);
    scene_make_hallway(scene_ptr, 13, 4, 20, 15);
    scene_make_hallway(scene_ptr, 22, 8, 28, 8);
    scene_make_hallway(scene_ptr, 15, 12, 19, 12);

    scene_set_tile(scene_ptr, 4, 4, TILE_PLAYER);
    scene_set_tile(scene_ptr, 7, 5, TILE_ENEMY);

    printf("Initialization finished, press any key.\n");
    getch();
}


void game_run()
{
    // game loop
    char input = '\n';
    while (input != 'q') {

        // update
        int update_return_code = 0;
        switch (get_current_game_state()) {

        case GAME_STATE_OVERWORLD:
            update_return_code = overworld_update(&s_game.overworld, input);
            break;

        case GAME_STATE_BATTLE:
            update_return_code = battle_update(&s_game.battle, input);
            switch (s_game.battle.status) {
            case BATTLE_STATUS_WON:
                s_game.cur_game_state = GAME_STATE_OVERWORLD;
                break;
            case BATTLE_STATUS_LOST:
                s_game.cur_game_state = GAME_STATE_GAMEOVER;
                break;
            }
            break;

        case GAME_STATE_GAMEOVER:
            update_return_code = gameover_update(&s_game.gameover, input);
            break;
        }

        // render
        if (update_return_code == 0 || input == '\n') {
            system("cls");
            display_clear();
            switch (get_current_game_state()) {
            case GAME_STATE_OVERWORLD:
                overworld_render(&s_game.overworld);
                break;
            case GAME_STATE_BATTLE:
                battle_render(&s_game.battle);
                break;
            case GAME_STATE_GAMEOVER:
                gameover_render(&s_game.gameover);
                break;
            }
            display_print();
        }
        input = getch();
    }
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
