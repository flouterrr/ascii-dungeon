#ifndef SCENE_H
#define SCENE_H

#include "defines.h"
#include "database.h"


typedef struct {
    int data[GRID_SIZE];
} scene_t;


void clear_scene(scene_t* scene);
int get_tile_id(scene_t* scene, int x, int y);
void set_tile(scene_t* scene, int x, int y, int tile_id);
void make_room(scene_t* scene, int pos_x, int pos_y, int width, int height);
void make_hallway(scene_t* scene, int from_x, int from_y, int to_x, int to_y);


#endif // SCENE_H
