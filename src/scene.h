#ifndef SCENE_H
#define SCENE_H

#include "defines.h"
#include "database.h"



typedef struct {
    int x;
    int y;
    int id;
} entity_t;


typedef struct {
    int tiles[GRID_SIZE];
    entity_t entities[MAX_ENTITIES];
} scene_t;


void scene_init(scene_t* scene);
void scene_clear(scene_t* scene);
int scene_get_tile_id(scene_t* scene, int x, int y);
void scene_set_tile(scene_t* scene, int x, int y, int tile_id);
void scene_make_room(scene_t* scene, int pos_x, int pos_y, int width, int height);
void scene_make_hallway(scene_t* scene, int from_x, int from_y, int to_x, int to_y);

void scene_add_entity(scene_t* scene, int entity_id, int x, int y);
void scene_entity_update(scene_t* scene, entity_t* entity, char input);
void scene_entity_move(scene_t* scene, entity_t* entity, int move_x, int move_y);


#endif // SCENE_H
