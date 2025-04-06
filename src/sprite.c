#include "sprite.h"


char* sprite_get_row(sprite_t* sprite, int row)
{
    if (row >= sprite->height) return NULL;

    return &sprite->data[row * (sprite->width + 1)];
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
    if (file_path == NULL)
    {
        printf("Failed to allocate memory for sprite file path.\n");
        return spr;
    }

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
    int cur_line_width_real = 0;
    int max_height = 0;

    while (true)
    {
        read_char = fgetc(fptr);
        if (read_char == EOF)
        { 
            max_height++;
            break;
        }
        else if (read_char == '\n')
        {
            max_height++;
            cur_line_width = 0;
            cur_line_width_real = 0;
        }
        else
        {
            cur_line_width++;
            if (read_char != ' ')
            {
                cur_line_width_real = cur_line_width;
            }
            max_width = cur_line_width_real > max_width ? cur_line_width_real : max_width;
        }
    }

    spr.width = max_width;
    spr.height = max_height;

    size_t data_size = sizeof(char) * ((spr.width + 1) * spr.height);
    spr.data = malloc(data_size);
    if (spr.data == NULL)
    {
        printf("Failed to allocate memory for sprite.\n");
        return spr;
    }

    memset(spr.data, '\0', data_size);

    fseek(fptr, 0, SEEK_SET);
    for (int y = 0; y < spr.height; y++)
    {
        char read_char = '\0';
        int x = 0;
        while(true)
        {
            read_char = fgetc(fptr);
            if (x >= spr.width) break;
            if (read_char == EOF || read_char == '\n') break;
            
            spr.data[x + (y * (spr.width + 1))] = read_char;
            x++;
        }
    }

    fclose(fptr);
    free(file_path);

    printf("%d x %d\n", spr.width, spr.height);
    for (int y = 0; y < spr.height; y++)
    {
        printf("row %d: %s\n", y+1, sprite_get_row(&spr, y));
    }

    return spr;
}


void unload_sprite(sprite_t* sprite)
{
    free(sprite->data);
}