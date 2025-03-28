#ifndef DATABASE_H
#define DATABASE_H

#include <stdbool.h>
#include <string.h>

#include "enums.h"
#include "sprite.h"


typedef struct {
    const char* icon; // 2 chars wide
    int text_color;
    int bg_color;
    bool bold;
    bool high_intensity;
} tile_data_t;


typedef struct {
    const char* name;
    sprite_t sprite;
    int hp;
    int atk;
} enemy_data_t;


typedef struct {
    tile_data_t tiles[NUM_TILES];
    enemy_data_t enemies[NUM_ENEMIES];
} database_t;

database_t g_database;


void init_database();
const tile_data_t* get_tile_data(int tile_id);
const enemy_data_t* get_enemy_data(int enemy_id);
void database_setup_tile(int tile_id, const char* icon, int text_color, int bg_color, bool bold, bool high_intensity);
void database_setup_enemy(int enemy_id, const char* name, int hp, int atk, bool large_sprite, const char* sprite_filename);


#endif // DATABASE_H
