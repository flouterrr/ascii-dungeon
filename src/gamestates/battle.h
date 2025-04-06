#ifndef BATTLE_H
#define BATTLE_H

#include <string.h>
#include <stdarg.h>
#include <Windows.h>

#include "database.h"
#include "defines.h"
#include "display.h"



typedef struct {
    int id;
    int num1;
} battle_action_t;


typedef struct {
    int id;
    union {
        char msg[MAX_BATTLE_MSG_LENGTH];
        int num1;
    };
} battle_event_t;


typedef struct {
    enemy_data_t* enemy;
    int enemy_cur_hp;
    int enemy_last_dmg_taken;
    bool enemy_dead;
    battle_action_t enemy_ba;

    int player_cur_hp;
    int player_last_dmg_taken;
    bool player_dead;
    battle_action_t player_ba;

    char msg[MAX_BATTLE_MSG_LENGTH];

    battle_event_t event_queue[MAX_BATTLE_EVENTS];
    int event_queue_length;
    int cur_event_index;
    int status;

} battle_t;


int battle_update(battle_t* battle, char input);
void battle_render(battle_t* battle);

void battle_add_event(battle_t* battle, int event_id, int num1);
void battle_add_event_msg(battle_t* battle, const char* msg, ...);
void battle_reset_event_queue(battle_t* battle);
void battle_run_event_queue(battle_t* battle);


#endif // BATTLE_H
