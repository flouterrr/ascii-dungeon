#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "enums.h"
#include "database.h"
#include "game.h"


int main()
{
    database_init();
    game_init();
    console_init();

    game_run();

    console_cleanup();
    return 0;
}
