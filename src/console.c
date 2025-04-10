#include "console.h"
#include <stdio.h>


#define ESC "\x1b"

static HANDLE s_out_handle;
static HANDLE s_in_handle;

static COLOR_T cur_fg_color = NULL;
static COLOR_T cur_bg_color = NULL;

static CONSOLE_CHAR_MODE_T cur_char_mode = NULL;


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
    printf(ESC "]2;%s\x07", "ASCII Dungeon");

    // switch to alternate screen buffer
    printf(ESC "[?1049h");

    // set console width
    printf(ESC "[?3l");
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
    if (cur_fg_color != fg_color)
    {
        printf(ESC "[%dm", fg_color);
        cur_fg_color = fg_color;
    }

    if (cur_bg_color != bg_color)
    {
        printf(ESC "[%dm", bg_color + 10);
        cur_bg_color = bg_color;
    }
    
}

void console_set_char_mode(CONSOLE_CHAR_MODE_T mode)
{
    if (cur_char_mode != mode)
    {
        printf(ESC "(%c", mode ? '0' : 'B');
        cur_char_mode = mode;
    }
}


void console_write_character(char c, CONSOLE_CHAR_MODE_T mode, COLOR_T fg_color, COLOR_T bg_color)
{
    console_set_color(fg_color, bg_color);
    console_set_char_mode(mode);
    printf("%c", c);
}


void console_replace_char(int x, int y, char c, CONSOLE_CHAR_MODE_T mode, COLOR_T fg_color, COLOR_T bg_color)
{
    printf(ESC "[%d;%df", y + 1, x + 1);
    console_set_color(fg_color, bg_color);
    console_set_char_mode(mode);
    printf("%c", c);
    printf(ESC "[?25l");
}


void console_clear()
{
    printf(ESC "[2J" ESC "[H");
}


void console_reset_color()
{
    printf(ESC "[0m");
}


#undef ESC