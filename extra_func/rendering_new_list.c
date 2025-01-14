#include "../header.h"


int add_empty_line(wifi_data *ptr_wifi_data, coord_win *coord, char list[][INT_64], int count_wifi_data_mod, char new_list[][MAX_LINE], _Bool bool_render_list)
{   
    int *width_win = &coord->width_win;
    char *interface = ptr_wifi_data->wifi_interface;
    char wifi_connected[64] = {0};

    if (bool_render_list) {
        check_connect(interface, wifi_connected);
    }

    for (int i = 0; i < count_wifi_data_mod; ++i) {
        size_t size_wifi_data = strlen(list[i]);
        int size_empty_line = *width_win - size_wifi_data - 2;

        if (size_empty_line < 0) {
            size_empty_line = 0;
        }

        char *empty_line = malloc(size_empty_line + 1);
        if (!empty_line) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return -1;
        }

        memset(empty_line, ' ', size_empty_line);
        empty_line[size_empty_line] = '\0';

        if (bool_render_list && strcmp(wifi_connected, list[i] + 1) == 0) {
            memcpy(empty_line + size_empty_line - 9, "connected", 9);
        }
        
        int size_fields = size_wifi_data + strlen(empty_line) + 1;
        snprintf(new_list[i], size_fields, "%s%s", list[i], empty_line);
        free(empty_line);
    }
}