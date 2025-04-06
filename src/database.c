#include "database.h"


static database_t s_database;


void database_setup_tile(int tile_id, const char* icon, COLOR_T fg_color, COLOR_T bg_color)
{
    tile_data_t* t = &s_database.tiles[tile_id];
    t->icon = icon;
    t->fg_color = fg_color;
    t->bg_color = bg_color;
}


void database_setup_sprite(int sprite_id, const char* sprite_filename)
{
    s_database.sprites[sprite_id] = load_new_sprite(sprite_filename);
}


void database_setup_enemy(int enemy_id, const char* name, int hp, int atk, int sprite_id)
{
    enemy_data_t* e = &s_database.enemies[enemy_id];
    e->name = name;
    e->hp = hp;
    e->atk = atk;
    e->sprite_id = sprite_id;
}


void database_init()
{
    database_setup_tile(TILE_AIR, "  ", COLOR_WHITE, COLOR_BLACK);
    database_setup_tile(TILE_WALL, "[]", COLOR_WHITE, COLOR_BLACK);
    database_setup_tile(TILE_PLAYER, "$@", COLOR_GREEN, COLOR_BLACK);
    database_setup_tile(TILE_ENEMY, "$@", COLOR_RED, COLOR_BLACK);

    database_setup_sprite(SPRITE_CAT, "cat");
    database_setup_sprite(SPRITE_BAT, "bat");
    database_setup_sprite(SPRITE_GUNTER, "gunter");
    database_setup_sprite(SPRITE_ORGALORG, "orgalorg");
    database_setup_sprite(SPRITE_GAMEOVER, "gameover");

    database_setup_enemy(ENEMY_CAT, "Cat", 9, 4, SPRITE_CAT);
    database_setup_enemy(ENEMY_BAT, "Bat", 4, 3, SPRITE_BAT);
    database_setup_enemy(ENEMY_GUNTER, "Gunter", 12, 6, SPRITE_GUNTER);
    database_setup_enemy(ENEMY_ORGALORG, "Orgalorg", 100, 20, SPRITE_ORGALORG);
}


const enemy_data_t* get_enemy_data(int enemy_id)
{
    return &s_database.enemies[enemy_id];
}


const tile_data_t* get_tile_data(int tile_id)
{
    return &s_database.tiles[tile_id];
}


const sprite_t* get_sprite(int sprite_id)
{
    return &s_database.sprites[sprite_id];
}


void database_cleanup()
{
    // sprite_t cleanup
    for (int i = 0; i < NUM_SPRITES; i++)
    {
        unload_sprite(&s_database.sprites[i]);
    }
}