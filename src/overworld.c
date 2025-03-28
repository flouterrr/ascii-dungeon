#include "overworld.h"


int overworld_update(overworld_t* overworld, char input)
{
    scene_t* scene_ptr = &overworld->scene;

    int p_x = 0;
    int p_y = 0;

    switch(input) {
    case 'w': // movement
        p_y = -1;
        break;
    case 'a':
        p_x = -1;
        break;
    case 's':
        p_y = 1;
        break;
    case 'd':
        p_x = 1;
        break;

    default:
        return 1;
    }

    tile_action_t tile_actions[MAX_TILE_ACTIONS];
    int tile_action_counter = 0;
    for(int i = 0; i < MAX_TILE_ACTIONS; i++) {
        tile_actions[i].tile_x = -1;
        tile_actions[i].tile_y = -1;
        tile_actions[i].move_x = 0;
        tile_actions[i].move_y = 0;
        tile_actions[i].change_tile_id = -1;
    }

    for(int y = 0; y < GRID_HEIGHT; y++) {
        for(int x = 0; x < GRID_WIDTH; x++) {
            if(get_tile_id(scene_ptr, x, y) == TILE_PLAYER) {
                tile_actions[tile_action_counter].tile_x = x;
                tile_actions[tile_action_counter].tile_y = y;
                tile_actions[tile_action_counter].move_x = p_x;
                tile_actions[tile_action_counter].move_y = p_y;
            }
        }
    }

    for(int i = 0; i < MAX_TILE_ACTIONS; i++) {
        tile_action_t* ta = &tile_actions[i];
        if(ta->tile_x == -1 || ta->tile_y == -1) {
            break;
        }

        if(ta->move_x != 0 || ta->move_y != 0) {
            int tile_id = get_tile_id(scene_ptr, ta->tile_x, ta->tile_y);
            int new_x = ta->tile_x + ta->move_x;
            int new_y = ta->tile_y + ta->move_y;

            int colliding_tile_id = get_tile_id(scene_ptr, new_x, new_y);
            if(colliding_tile_id == TILE_WALL) continue;
            else if(colliding_tile_id == TILE_ENEMY) {
                start_battle();
            }

            set_tile(scene_ptr, new_x, new_y, tile_id);
            set_tile(scene_ptr, ta->tile_x, ta->tile_y, TILE_AIR);
        }
    }

    return 0;
}


void overworld_render(overworld_t* overworld)
{
    scene_t* scene_ptr = &overworld->scene;

    for(int y = 0; y < GRID_HEIGHT; y++) {
        for(int x = 0; x < GRID_WIDTH; x++) {

            tile_data_t* tile = get_tile_data(get_tile_id(scene_ptr, x, y));

            int bold_num = tile->bold ? 1 : 0;
            int hi_num = tile->high_intensity ? 9 : 3;
            switch(tile->text_color) {
            case COLOR_WHITE:
                printf("\e[%d;%d7m", bold_num, hi_num);
                break;
            case COLOR_RED:
                printf("\e[%d;%d1m", bold_num, hi_num);
                break;
            case COLOR_YELLOW:
                printf("\e[%d;%d3m", bold_num, hi_num);
                break;
            case COLOR_BLUE:
                printf("\e[%d;%d4m", bold_num, hi_num);
                break;
            case COLOR_GREEN:
                printf("\e[%d;%d2m", bold_num, hi_num);
                break;
            case COLOR_BLACK:
                printf("\e[%d;%d0m", bold_num, hi_num);
                break;
            case COLOR_CYAN:
                printf("\e[%d;%d6m", bold_num, hi_num);
                break;
            case COLOR_MAGENTA:
                printf("\e[%d;%d5m", bold_num, hi_num);
                break;
            }

            switch(tile->bg_color) {
            case COLOR_WHITE:
                printf("\e[47m");
                break;
            case COLOR_RED:
                printf("\e[41m");
                break;
            case COLOR_YELLOW:
                printf("\e[43m");
                break;
            case COLOR_BLUE:
                printf("\e[44m");
                break;
            case COLOR_GREEN:
                printf("\e[42m");
                break;
            case COLOR_BLACK:
                printf("\e[40m");
                break;
            case COLOR_CYAN:
                printf("\e[46m");
                break;
            case COLOR_MAGENTA:
                printf("\e[45m");
                break;
            }

            printf("%s\e[0m", tile->icon);
        }
        printf("\n");
    }
}
