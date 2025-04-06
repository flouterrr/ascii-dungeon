#include "console.h"
#include <stdio.h>

static HANDLE s_out_handle;
static HANDLE s_in_handle;

#define ESC "\x1b"

void console_init()
{
    s_out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    s_in_handle = GetStdHandle(STD_INPUT_HANDLE);

    //SetConsoleTitle(TEXT("ASCII Dungeon"));

    // enable virtual terminal sequences
    DWORD dw_original_out_mode = 0;
    DWORD dw_original_in_mode = 0;
    GetConsoleMode(s_out_handle, &dw_original_out_mode);
    GetConsoleMode(s_in_handle, &dw_original_in_mode);
    DWORD dw_requested_out_modes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dw_requested_in_modes = ENABLE_VIRTUAL_TERMINAL_INPUT;
    DWORD dw_out_mode = dw_original_out_mode | dw_requested_out_modes;
    SetConsoleMode(s_out_handle, dw_out_mode);
    DWORD dw_in_mode = dw_original_in_mode | dw_requested_in_modes;

    // disable cursor
    printf(ESC "[?25l");

    // setting the console title
    printf(ESC "]2;%s\x07", "ASCII Dunegeon");

    // switch to alternate screen buffer
    printf(ESC "[?1049h");
}


void console_cleanup()
{
    // switch to main screen buffer
    printf(ESC "[?1049l");

    // enable cursor
    printf(ESC "[?25h");
}


void console_set_color(COLOR_T fg_color, COLOR_T bg_color)
{
    printf(ESC "[%dm", fg_color);
    printf(ESC "[%dm", bg_color + 10);
}

void console_reset_color()
{
    printf(ESC "[0m");
}

#undef ESC