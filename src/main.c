#include <stdio.h>
#include <stdlib.h>

#include "console.h"
#include "enums.h"
#include "database.h"
#include "game.h"


int main()
{
    /*
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    const CONSOLE_CURSOR_INFO cursor_info = {
        .dwSize = 100,
        .bVisible = false
    };
    SetConsoleCursorInfo(console_handle, &cursor_info);
    SetConsoleTitle("ASCII Dungeon");
    */

    database_init();
    game_init();
    console_init();

    game_run();

    console_cleanup();
    return 0;
}
