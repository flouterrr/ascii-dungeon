#ifndef SCENE_H
#define SCENE_H

#include "defines.h"
#include "database.h"


typedef struct {
    int data[GRID_SIZE];
} scene_t;


void scene_clear(scene_t* scene);
int scene_get_tile_id(scene_t* scene, int x, int y);
void scene_set_tile(scene_t* scene, int x, int y, int tile_id);
void scene_make_room(scene_t* scene, int pos_x, int pos_y, int width, int height);
void scene_make_hallway(scene_t* scene, int from_x, int from_y, int to_x, int to_y);


#endif // SCENE_H
