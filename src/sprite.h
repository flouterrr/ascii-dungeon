#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    bool large_sprite;
    char data[8 * 32];
} sprite_t;

sprite_t load_sprite(const char* filename, bool large);
char* sprite_get_row(sprite_t* sprite, int row);

#endif // SPRITE_H
