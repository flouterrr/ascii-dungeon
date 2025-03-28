#include "database.h"


void database_setup_tile(int tile_id, const char* icon, int text_color, int bg_color, bool bold, bool high_intensity)
{
    tile_data_t* t = &g_database.tiles[tile_id];
    t->icon = icon;
    t->text_color = text_color;
    t->bg_color = bg_color;
    t->bold = bold;
    t->high_intensity = high_intensity;
}


void database_setup_enemy(int enemy_id, const char* name, int hp, int atk, bool large_sprite, const char* sprite_filename)
{
    enemy_data_t* e = &g_database.enemies[enemy_id];
    e->name = name;
    e->hp = hp;
    e->atk = atk;
    e->sprite = load_sprite(sprite_filename, large_sprite);
}


void init_database()
{

    // test line

    database_setup_tile(TILE_AIR, "  ", COLOR_WHITE, COLOR_BLACK, false, false);
    database_setup_tile(TILE_WALL, "[]", COLOR_WHITE, COLOR_BLACK, false, false);
    database_setup_tile(TILE_PLAYER, "$@", COLOR_GREEN, COLOR_BLACK, true, true);
    database_setup_tile(TILE_ENEMY, "$@", COLOR_RED, COLOR_BLACK, true, true);

    database_setup_enemy(ENEMY_CAT, "Cat", 9, 4, false, "cat");
    database_setup_enemy(ENEMY_BAT, "Bat", 4, 3, false, "bat");
    database_setup_enemy(ENEMY_GUNTER, "Gunter", 12, 6, false, "gunter");
    database_setup_enemy(ENEMY_ORGALORG, "Orgalorg", 100, 20, true, "orgalorg");
}


const enemy_data_t* get_enemy_data(int enemy_id)
{
    return &g_database.enemies[enemy_id];
}


const tile_data_t* get_tile_data(int tile_id)
{
    return &g_database.tiles[tile_id];
}
