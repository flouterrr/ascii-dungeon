#include "scene.h"
#include "game.h"
#include "utils.h"


void scene_init(scene_t* scene)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        entity_t* entity = &scene->entities[i];
        entity->id = -1;
    }

    scene_clear(scene);
}


void scene_clear(scene_t* scene)
{
    for(int i = 0; i < GRID_SIZE; i++) {
        scene->tiles[i] = TILE_AIR;
    }
}


int scene_get_tile_id(scene_t* scene, int x, int y)
{
    return scene->tiles[x + (GRID_WIDTH * y)];
}


void scene_set_tile(scene_t* scene, int x, int y, int tile_id)
{
    scene->tiles[x + (GRID_WIDTH * y)] = tile_id;
}


void scene_make_room(scene_t* scene, int pos_x, int pos_y, int width, int height)
{
    for(int y = pos_y; y < pos_y + height; y++) {
        for(int x = pos_x; x < pos_x + width; x++) {
            if(x == pos_x || x == pos_x + width - 1 || y == pos_y || y == pos_y + height - 1) {
                scene_set_tile(scene, x, y, TILE_WALL);
            }
        }
    }
}


void scene_make_hallway(scene_t* scene, int from_x, int from_y, int to_x, int to_y)
{
    int stage = 0;
    while(stage < 2) {
        int cur_x = from_x;
        int cur_y = from_y;

        int d_x = 0;
        int d_y = 0;

        while(cur_x != to_x || cur_y != to_y) {
            if(cur_x < to_x) {
                d_x = 1;
                d_y = 0;
            } else if(cur_x > to_x) {
                d_x = -1;
                d_y = 0;
            } else if(cur_y < to_y) {
                d_x = 0;
                d_y = 1;
            } else if(cur_y > to_y) {
                d_x = 0;
                d_y = -1;
            }

            if(stage == 0) {
                for(int i = -1; i <= 1; i++) {
                    for(int j = -1; j <= 1; j++) {
                        scene_set_tile(scene, cur_x + i, cur_y + j, TILE_WALL);
                    }
                }
                if(cur_x == from_x && cur_y == from_y) {
                    scene_set_tile(scene, cur_x - d_x, cur_y - d_y, TILE_AIR);
                } else if((cur_x + d_x) == to_x && (cur_y + d_y) == to_y) {
                    scene_set_tile(scene, cur_x + d_x, cur_y + d_y, TILE_AIR);
                }
            } else if(stage == 1) {
                scene_set_tile(scene, cur_x, cur_y, TILE_AIR);
            }

            cur_x += d_x;
            cur_y += d_y;
        }
        stage++;
    }
}


entity_t* scene_find_free_entity(scene_t* scene)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        entity_t* entity = &scene->entities[i];
        if (entity->id == -1) return entity;
    }
    return NULL;
}


entity_t* scene_add_entity(scene_t* scene, int entity_id, int x, int y)
{
    entity_t* entity = scene_find_free_entity(scene);
    if (entity == NULL) return NULL;

    entity->id = entity_id;
    entity->x = x;
    entity->y = y;

    // variable initialization
    switch (entity->id)
    {
    case ENTITY_ENEMY:
        entity->enemy.battle_id = 0;
        entity->enemy.move_x = 0;
        entity->enemy.move_y = 0;
        break;
    }

    return entity;
}


void scene_entity_update(scene_t* scene, entity_t* entity, char input)
{
    switch (entity->id)
    {

    case ENTITY_PLAYER:
        // player movement
        int p_x = (int)(input == 'd') - (int)(input == 'a');
        int p_y = (int)(input == 's') - (int)(input == 'w');
        scene_entity_move(scene, entity, p_x, p_y);
        break;

    case ENTITY_ENEMY:
        bool move_successful = scene_entity_move(scene, entity, entity->enemy.move_x, entity->enemy.move_y);
        if (!move_successful)
        {
            entity->enemy.move_x = -entity->enemy.move_x;
            entity->enemy.move_y = -entity->enemy.move_y;
            scene_entity_move(scene, entity, entity->enemy.move_x, entity->enemy.move_y);
        }
        break;
    }
}


void scene_entity_post_update(scene_t* scene, entity_t* entity, char input)
{
    switch (entity->id)
    {
    case ENTITY_PLAYER:
        break;
        
    case ENTITY_ENEMY:
        break;
    }
}


void scene_entity_collision_resolve(scene_t* scene, entity_t* e1, entity_t* e2)
{
    for (int i = 0; i < 2; i++)
    {
        if (e1->id == ENTITY_PLAYER && e2->id == ENTITY_ENEMY)
        {
            start_battle(e2->enemy.battle_id);
        }

        entity_t* temp = e2;
        e2 = e1;
        e1 = temp;
    }
}


bool scene_entity_move(scene_t* scene, entity_t* entity, int move_x, int move_y)
{
    if (move_x == 0 && move_y == 0) return false;

    int new_x = entity->x + move_x;
    int new_y = entity->y + move_y;
    
    int colliding_tile_id = scene_get_tile_id(scene, new_x, new_y);
    tile_data_t* tile_data = get_tile_data(colliding_tile_id);
    if (tile_data->solid) return false;

    // check for entity collision
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        entity_t* col_e = &scene->entities[i];
        if (col_e->id == -1) continue;

        if (col_e->x == new_x && col_e->y == new_y)
        {
            scene_entity_collision_resolve(scene, entity, col_e);
        }
    }

    entity->x = new_x;
    entity->y = new_y;
    return true;
}


