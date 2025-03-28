#include "utils.h"


int randint(int n)
{
    if((n - 1) == RAND_MAX) return rand();

    assert(n <= RAND_MAX);

    int x;
    do {
        x = rand();
    } while (x >= (RAND_MAX - RAND_MAX % n));

    return x % n;
}


int colorToConsoleHex(int color_id)
{
    int hex = 0x00;
    switch (color_id)
    {
    case COLOR_WHITE:
        hex = 0x07;
        break;
    case COLOR_BRIGHT_WHITE:
        hex = 0x0F;
        break;
    case COLOR_BLACK:
        hex = 0x00;
        break;
    case COLOR_GREY:
        hex = 0x08;
        break;
    case COLOR_RED:
        hex = 0x04;
        break;
    case COLOR_LIGHT_RED:
        hex = 0x0C;
        break;
    case COLOR_YELLOW:
        hex = 0x06;
        break;
    case COLOR_LIGHT_YELLOW:
        hex = 0x0E;
        break;
    case COLOR_BLUE:
        hex = 0x01;
        break;
    case COLOR_LIGHT_BLUE:
        hex = 0x09;
        break;
    case COLOR_GREEN:
        hex = 0x02;
        break;
    case COLOR_LIGHT_GREEN:
        hex = 0x0A;
        break;
    case COLOR_CYAN:
        hex = 0x03;
        break;
    case COLOR_LIGHT_CYAN:
        hex = 0x0B;
        break;
    case COLOR_MAGENTA:
        hex = 0x05;
        break;
    case COLOR_LIGHT_MAGENTA:
        hex = 0x0D;
        break;
    }

    return hex;
}
