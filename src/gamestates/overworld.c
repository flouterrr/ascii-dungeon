#include "overworld.h"


int overworld_update(overworld_t* overworld, char input)
{
    scene_t* scene_ptr = &overworld->scene;

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (scene_ptr->entities[i].id != -1)
        {
            scene_entity_update(scene_ptr, &scene_ptr->entities[i], input);
        }
    }

    return 0;
}


void overworld_render(overworld_t* overworld)
{
    scene_t* scene_ptr = &overworld->scene;

    // render tiles
    for(int y = 0; y < GRID_HEIGHT; y++) {
        for(int x = 0; x < GRID_WIDTH; x++) {
            tile_data_t* tile = get_tile_data(scene_get_tile_id(scene_ptr, x, y));
            display_set_cell(x * 2, y, tile->icon[0], tile->fg_color, tile->bg_color, false);
            display_set_cell((x * 2) + 1, y, tile->icon[1], tile->fg_color, tile->bg_color, false);
        }
    }

    // render entites
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_t* entity = &scene_ptr->entities[i];
        if (entity->id != -1)
        {
            entity_data_t* entity_data = get_entity_data(entity->id);
            display_set_cell(entity->x * 2, entity->y, entity_data->icon[0], entity_data->fg_color, entity_data->bg_color, false);
            display_set_cell((entity->x * 2) + 1, entity->y, entity_data->icon[1], entity_data->fg_color, entity_data->bg_color, false);
        }
    }
}
