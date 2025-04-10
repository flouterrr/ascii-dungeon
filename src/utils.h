#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <enums.h>
#include <assert.h>

#include "console.h"	


int randint(int n);
unsigned char dec_line_char_to_line_bits(char c);
char line_bits_to_dec_line_char(unsigned char b);


#endif // UTILS_H
