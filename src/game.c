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
    scene_init(scene_ptr);

    scene_make_room(scene_ptr, 1, 1, 12, 8);
    scene_make_room(scene_ptr, 17, 15, 18, 6);
    scene_make_room(scene_ptr, 28, 5, 10, 8);
    scene_make_room(scene_ptr, 3, 10, 12, 10);
    scene_make_hallway(scene_ptr, 13, 4, 20, 15);
    scene_make_hallway(scene_ptr, 22, 8, 28, 8);
    scene_make_hallway(scene_ptr, 15, 12, 19, 12);

    scene_add_entity(scene_ptr, ENTITY_PLAYER, 4, 4);
    {
        entity_t* enemy = scene_add_entity(scene_ptr, ENTITY_ENEMY, 7, 5);
        enemy->enemy.battle_id = ENEMY_GUNTER;
        enemy->enemy.move_y = -1;
    }

    {
        entity_t* enemy = scene_add_entity(scene_ptr, ENTITY_ENEMY, 9, 4);
        enemy->enemy.battle_id = ENEMY_ORGALORG;
    }

    {
        entity_t* enemy = scene_add_entity(scene_ptr, ENTITY_ENEMY, 5, 7);
        enemy->enemy.battle_id = ENEMY_CAT;
        enemy->enemy.move_x = 1;
    }

    printf("Initialization finished, press any key.\n");
    getch();
}


void game_run()
{
    display_draw_border();
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
            display_refresh();
        }
        input = getch();
    }
}


int get_current_game_state()
{
    return s_game.cur_game_state;
}


void start_battle(int enemy_id)
{
    battle_init(&s_game.battle, enemy_id);
    s_game.cur_game_state = GAME_STATE_BATTLE;
}
