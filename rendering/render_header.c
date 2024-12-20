#include "../header.h"


int render_header(wifi_data *ptr_wifi_data, coord_win *coord, cursor *curs, WINDOW *header, _Bool *active)
{
    int *cur_header = &coord->cur_header;
    char fields[4][256];
    form_header(ptr_wifi_data, coord, fields);
  
    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    *active ? wbkgd(header, COLOR_PAIR(13)) : wbkgd(header, COLOR_PAIR(1));

    for (int i = 0, j = 1; i < 4; ++i, ++j) {
        wattron(header, A_BOLD);
        if (*cur_header == j) {
            wattron(header, COLOR_PAIR(2));
            mvwprintw(header, j, 1, "%s", fields[i]);
            wattroff(header, COLOR_PAIR(2));
        } else {
            mvwprintw(header, j, 1, "%s", fields[i]);
        }
        wattroff(header, A_BOLD);
    }

    wrefresh(header);
    printf("\n");
}



int form_header(wifi_data *ptr_wifi_data, coord_win *coord, char fields[][256])
{
    int *width_win = &coord->width_win;
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    int *wifi_status = &ptr_wifi_data->wifi_status;
    char *wifi_IP = ptr_wifi_data->wifi_IP;
    char *wifi_mask = ptr_wifi_data->wifi_mask;
    char *gateway_default = ptr_wifi_data->gateway_default;

    char wifi_data_mod[4][64];
    snprintf(wifi_data_mod[0], strlen(wifi_interface) + 14, " Interface:  %s", wifi_interface);
    snprintf(wifi_data_mod[1], strlen(*wifi_status == 0 ? "UP" : "DUWN") + 14, " Status:     %s", *wifi_status == 0 ? "UP" : "DUWN");
    snprintf(wifi_data_mod[2], strlen(wifi_IP) + strlen(wifi_mask) + 14, " IP:         %s%s", wifi_IP, wifi_mask);
    snprintf(wifi_data_mod[3], strlen(gateway_default) + 14, " Gateway:    %s", gateway_default);


    for (int i = 0; i < 4; ++i) {
        size_t size_wifi_data = strlen(wifi_data_mod[i]);
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
        
        int size_fields = size_wifi_data + strlen(empty_line) + 1;
        snprintf(fields[i], size_fields, "%s%s", wifi_data_mod[i], empty_line);
        free(empty_line);
    }
}

