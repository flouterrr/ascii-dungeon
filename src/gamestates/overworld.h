#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <Windows.h>

#include "scene.h"
#include "utils.h"
#include "display.h"


typedef struct {
    scene_t scene;
} overworld_t;


typedef struct {
    int tile_x;
    int tile_y;
    int move_x;
    int move_y;
    int change_tile_id;
} tile_action_t;


int overworld_update(overworld_t* overworld, char input);
void overworld_render(overworld_t* overworld);


#endif // OVERWORLD_H
