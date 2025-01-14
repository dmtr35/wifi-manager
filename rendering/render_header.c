#include "../header.h"


int render_header(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *header, _Bool *active)
{
    int *cur_header = &coord->cur_header;
    char fields[4][MAX_LINE];
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
}


int form_header(wifi_data *ptr_wifi_data, coord_win *coord, char fields[][MAX_LINE])
{
    int *width_win = &coord->width_win;
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    int *wifi_status = &ptr_wifi_data->wifi_status;
    char *wifi_IP = ptr_wifi_data->wifi_IP;
    char *wifi_mask_cidr = ptr_wifi_data->wifi_mask_cidr;
    char *gateway_default = ptr_wifi_data->gateway_default;

    int count_wifi_data_mod = 4;
    char wifi_data_mod[count_wifi_data_mod][INT_64];
    snprintf(wifi_data_mod[0], strlen(wifi_interface) + 14, " Interface:  %s", wifi_interface);
    snprintf(wifi_data_mod[1], strlen(*wifi_status == 1 ? "UP" : "DUWN") + 14, " Status:     %s", *wifi_status == 1 ? "UP" : "DUWN");
    snprintf(wifi_data_mod[2], strlen(wifi_IP) + strlen(wifi_mask_cidr) + 14, " IP:         %s%s", wifi_IP, wifi_mask_cidr);
    snprintf(wifi_data_mod[3], strlen(gateway_default) + 14, " Gateway:    %s", gateway_default);

    add_empty_line(ptr_wifi_data, coord, wifi_data_mod, count_wifi_data_mod, fields, 0);
}




