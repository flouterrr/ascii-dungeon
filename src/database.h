#ifndef DATABASE_H
#define DATABASE_H

#include <stdbool.h>
#include <string.h>

#include "enums.h"
#include "sprite.h"
#include "color.h"


typedef struct {
    const char* icon; // 2 chars wide
    COLOR_T fg_color;
    COLOR_T bg_color;
} tile_data_t;


typedef struct {
    const char* name;
    int sprite_id;
    int hp;
    int atk;
} enemy_data_t;


typedef struct {
    tile_data_t tiles[NUM_TILES];
    enemy_data_t enemies[NUM_ENEMIES];
    sprite_t sprites[NUM_SPRITES];
} database_t;

database_t g_database;


void database_init();
const tile_data_t* get_tile_data(int tile_id);
const enemy_data_t* get_enemy_data(int enemy_id);
const sprite_t* get_sprite(int sprite_id);
void database_setup_tile(int tile_id, const char* icon, COLOR_T fg_color, COLOR_T bg_color);
void database_setup_sprite(int sprite_id, const char* sprite_filename);
void database_setup_enemy(int enemy_id, const char* name, int hp, int atk, int sprite_id);
void database_cleanup();


#endif // DATABASE_H
