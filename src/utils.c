#include "utils.h"


static char s_dec_line_chars[DEC_LINE_COUNT] = {
    DEC_LINE_H,         // 0
    DEC_LINE_V,         // 1
    DEC_LINE_TL,        // 2
    DEC_LINE_TR,        // 3
    DEC_LINE_BL,        // 4
    DEC_LINE_BR,        // 5
    DEC_LINE_T_RIGHT,   // 6
    DEC_LINE_T_LEFT,    // 7
    DEC_LINE_T_UP,      // 8
    DEC_LINE_T_DOWN,    // 9
    DEC_LINE_CROSS      // 10
};

static unsigned char s_dec_line_bits[DEC_LINE_COUNT] = {
    0b00001010,         // 0
    0b00000101,         // 1
    0b00000110,         // 2
    0b00001100,         // 3
    0b00000011,         // 4
    0b00001001,         // 5
    0b00000111,         // 6
    0b00001101,         // 7
    0b00001011,         // 8
    0b00001110,         // 9
    0b00001111          // 10
};


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

unsigned char dec_line_char_to_line_bits(char c)
{
    unsigned char b = 0;
    for (int i = 0; i < DEC_LINE_COUNT; i++)
    {
        if (s_dec_line_chars[i] == c)
        {
            b = s_dec_line_bits[i];
        }
    }
    return b;
}


char line_bits_to_dec_line_char(unsigned char b)
{
    char c = '\0';
    for (int i = 0; i < DEC_LINE_COUNT; i++)
    {
        if (s_dec_line_bits[i] == b)
        {
            c = s_dec_line_chars[i];
        }
    }
    return c;
}
