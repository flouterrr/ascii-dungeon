#include "battle.h"


void battle_add_event(battle_t* battle, int event_id, int num1)
{
    battle_event_t* event = &battle->event_queue[battle->event_queue_length];
    event->id = event_id;
    event->num1 = num1;

    battle->event_queue_length += 1;
}


void battle_add_event_msg(battle_t* battle, const char* msg, ...)
{
    battle_event_t* event = &battle->event_queue[battle->event_queue_length];
    event->id = BE_MSG;

    va_list args;
    va_start(args, msg);
    vsprintf(event->msg, msg, args);
    va_end(args);

    battle->event_queue_length += 1;
}


void battle_reset_event_queue(battle_t* battle)
{
    battle->cur_event_index = 0;
    battle->event_queue_length = 0;
}


void battle_run_event_queue(battle_t* battle)
{
    do {
        if(battle->cur_event_index == battle->event_queue_length) {
            battle_reset_event_queue(battle);
            strcpy(battle->msg, "");
            return;
        }

        battle_event_t* event = &battle->event_queue[battle->cur_event_index];

        switch(event->id) {
        case BE_MSG:
            strncpy(battle->msg, event->msg, MAX_BATTLE_MSG_LENGTH);
            break;

        case BE_ENEMY_TAKE_DMG:
            battle->enemy_cur_hp -= event->num1;
            battle->enemy_last_dmg_taken = event->num1;
            break;

        case BE_PLAYER_TAKE_DMG:
            battle->player_cur_hp -= event->num1;
            battle->player_last_dmg_taken = event->num1;
            break;

        case BE_PLAYER_RUN_AWAY:
            break;

        case BE_ENEMY_RUN_AWAY:
            break;

        case BE_WIN_BATTLE:
            battle->status = BATTLE_STATUS_WON;
            break;

        case BE_LOSE_BATTLE:
            battle->status = BATTLE_STATUS_LOST;
            break;
        }

        battle->cur_event_index += 1;
        if(event->id == BE_MSG) break;

    } while(battle->cur_event_index < battle->event_queue_length);
}


int battle_init(battle_t* battle, int enemy_id)
{
    enemy_data_t* enemy = get_enemy_data(enemy_id);
    battle->enemy = enemy;
    battle->enemy_cur_hp = enemy->hp;
    battle->enemy_dead = false;

    battle->player_cur_hp = 10;
    battle->player_dead = false;

    battle_reset_event_queue(battle);
    battle->status = BATTLE_STATUS_ACTIVE;
}


int battle_update(battle_t* battle, char input)
{
    battle->enemy_last_dmg_taken = 0;
    battle->player_last_dmg_taken = 0;

    if(battle->event_queue_length > 0) {
        if(input != '\r' && input != ' ') return 1;

        battle_run_event_queue(battle);

        if(battle->enemy_cur_hp <= 0 && !battle->enemy_dead) {
            battle->enemy_dead = true;
            battle_reset_event_queue(battle);
            battle_add_event_msg(battle, "%s was slain!", battle->enemy->name);
            battle_add_event(battle, BE_WIN_BATTLE, 0);
        } else if(battle->player_cur_hp <= 0 && !battle->player_dead) {
            battle->player_dead = true;
            battle_reset_event_queue(battle);
            battle_add_event_msg(battle, "Player died...");
            battle_add_event(battle, BE_LOSE_BATTLE, 0);
        }

        return 0;
    }

    // player picks action
    switch(input) {
    case 'a': // attack
        battle->player_ba.id = BA_ATTACK;
        battle->player_ba.num1 = 3;
        break;

    case 'd': // defend
        battle->player_ba.id = BA_DEFEND;
        break;

    case 'r': // run
        battle->player_ba.id = BA_RUN;
        break;

    default:
        return 1;
    }

    // enemy picks action
    battle->enemy_ba.id = BA_ATTACK;
    battle->enemy_ba.num1 = battle->enemy->atk;

    // player action evaluation
    switch(battle->player_ba.id) {
    case BA_ATTACK:
        battle_add_event_msg(battle, "Player attacks %s...", battle->enemy->name);
        int dmg = battle->player_ba.num1;
        if(battle->enemy_ba.id == BA_DEFEND) {
            dmg = 1;
            battle_add_event_msg(battle, "but %s defends!", battle->enemy->name);
        }
        battle_add_event(battle, BE_ENEMY_TAKE_DMG, dmg);
        battle_add_event_msg(battle, "%s takes %d damage.", battle->enemy->name, dmg);
        break;

    case BA_DEFEND:
        battle_add_event_msg(battle, "Player holds steady.");
        break;

    case BA_RUN:
        battle_add_event_msg(battle, "Player tried to run...");
        battle_add_event_msg(battle, "but failed!");
        break;
    }

    // enemy action evaluation
    switch(battle->enemy_ba.id) {
    case BA_ATTACK:
        battle_add_event_msg(battle, "The %s attacks!", battle->enemy->name);
        int dmg = battle->enemy_ba.num1;
        if(battle->player_ba.id == BA_DEFEND) {
            dmg = 1;
        }
        battle_add_event(battle, BE_PLAYER_TAKE_DMG, dmg);
        battle_add_event_msg(battle, "Player takes %d damage.", dmg);
        break;

    case BA_DEFEND:
        break;

    case BA_RUN:
        battle_add_event_msg(battle, "%s tried to run...", battle->enemy->name);
        break;
    }

    battle_run_event_queue(battle);
    return 0;
}


void battle_render(battle_t* battle)
{
    // enemy sprite
    display_render_sprite(
        battle->enemy->sprite_id, 
        DISPLAY_WIDTH / 2, 8, true, 
        COLOR_WHITE, COLOR_BLACK
    );

    // enemy info
    bool show_dmg = battle->enemy_last_dmg_taken > 0;
    char* dmg_text[20];
    if (show_dmg)
    {
        snprintf(dmg_text, 20, "(-%d)", battle->enemy_last_dmg_taken);
    }

    display_render_box(
        DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 10, true, 30, 3, true,
        COLOR_GREY, COLOR_BLACK
    );
    display_render_text(
        DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 10, true, 
        COLOR_WHITE, COLOR_BLACK,
        "%s HP:%d %s", 
        battle->enemy->name,
        battle->enemy_cur_hp,
        show_dmg ? dmg_text : ""
    );

    // player info
    show_dmg = battle->player_last_dmg_taken > 0;
    if (show_dmg)
    {
        snprintf(dmg_text, 20, "(-%d)", battle->player_last_dmg_taken);
    }
    display_render_box(
        DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 7, true, 30, 3, true,
        COLOR_GREY, COLOR_BLACK
    );
    display_render_text(
        DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 7, true,
        COLOR_WHITE, COLOR_BLACK,
        "YOUR HP:%d %s", battle->player_cur_hp, show_dmg ? dmg_text : ""
    );

    // player choices
    if (battle->event_queue_length == 0) 
    {
        display_render_box(
            DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 5, true, 30, 3, true,
            COLOR_GREY, COLOR_BLACK
        );
        display_render_text(
            DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 5, true,
            COLOR_WHITE, COLOR_BLACK,
            "[A]ttack [D]efend [R]un"
        );
    }
    else
    {
        display_render_box(
            DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 3, true, 50, 5, true,
            COLOR_GREY, COLOR_BLACK
        );
        display_render_text(
            DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 3, true,
            COLOR_WHITE, COLOR_BLACK,
            "\n%s\n", battle->msg
        );
    }

}
