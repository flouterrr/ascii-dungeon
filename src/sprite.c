#include "sprite.h"


char* sprite_get_row(sprite_t* sprite, int row)
{
    return &sprite->data[row * 32];
}


sprite_t load_sprite(const char* filename, bool large)
{
    /*
    sprite_t spr;
    spr.large_sprite = large;

    const char* folder_path = PROJECT_ROOT_DIR "assets/battle_sprites/";
    const char* file_ext = ".txt";
    int full_path_len = strlen(folder_path) + strlen(filename) + strlen(file_ext);
    char* file_path = malloc(sizeof(char) * (full_path_len + 1));
    sprintf(file_path, "%s%s%s", folder_path, filename, file_ext);

    FILE* fptr = fopen(file_path, "r");

    if(fptr == NULL)
    {
        printf("Failed to load file \"%s\"\n", file_path);
        return spr;
    }
    else
    {
        printf("File \"%s\" loaded successfully\n", file_path);
    }

    int row_count = large ? 8 : 4;
    int max_chars = large ? 32 : 16;
    char read_char = '\0';
    for(int i = 0; i < row_count; i++)
    {
        int char_index = 0;

        while(true)
        {
            read_char = fgetc(fptr);
            if(read_char == EOF || read_char == '\n') break;

            spr.data[(i * 32) + char_index] = read_char;
            char_index++;
        }
        spr.data[(i * 32) + char_index] = '\0';
        char_index++;

        printf("row %d: %s\n", i, sprite_get_row(&spr, i));
    }

    fclose(fptr);
    free(file_path);
    return spr;
    */
}


sprite_t load_new_sprite(const char* filename)
{
    sprite_t spr;
    spr.width = 0;
    spr.height = 0;
    spr.data = NULL;

    const char* folder_path = PROJECT_ROOT_DIR "assets/";
    const char* file_ext = ".txt";
    int full_path_len = strlen(folder_path) + strlen(filename) + strlen(file_ext);
    char* file_path = malloc(sizeof(char) * (full_path_len + 1));
    sprintf(file_path, "%s%s%s", folder_path, filename, file_ext);

    FILE* fptr = fopen(file_path, "r");

    if (fptr == NULL)
    {
        printf("Failed to load file \"%s\"\n", file_path);
        return spr;
    }
    else
    {
        printf("File \"%s\" loaded successfully\n", file_path);
    }

    char read_char = '\0';
    int max_width = 0;
    int cur_line_width = 0;
    int max_height = 0;

    while (true)
    {
        read_char = fgetc(fptr);
        if (read_char == EOF) break;
        else if (read_char == '\n')
        {
            max_height++;
            cur_line_width = 0;
        }
        else
        {
            cur_line_width++;
            max_width = cur_line_width > max_width ? cur_line_width : max_width;
        }
    }

    spr.width = max_width;
    spr.height = max_height;

    size_t data_size = sizeof(char) * spr.width * spr.height;
    spr.data = malloc(data_size);
    memset(spr.data, 0, data_size);

    fseek(fptr, 0, SEEK_SET);
    for (int y = 0; y < spr.height; y++)
    {
        char read_char = '\0';
        for (int x = 0; x < spr.width; x++)
        {
            read_char = fgetc(fptr);
            if (read_char == EOF || read_char == '\n') break;

            spr.data[x + (y * spr.width)] = read_char;
        }
    }

    fclose(fptr);
    free(file_path);
    return spr;
}