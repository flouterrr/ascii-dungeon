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
