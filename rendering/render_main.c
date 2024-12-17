#include "../header.h"


int render_main(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *header, WINDOW *list)
{
    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;
    
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    char *wifi_status = ptr_wifi_data->wifi_status;
    char *wifi_IP = ptr_wifi_data->wifi_IP;
    char *wifi_mask = ptr_wifi_data->wifi_mask;
    char *gateway_default = ptr_wifi_data->gateway_default;

    wattron(header, A_BOLD);
    mvwprintw(header, 0, 1, " Interface:  %s", wifi_interface);
    mvwprintw(header, 1, 1, " Status:     %s", wifi_status);
    mvwprintw(header, 2, 1, " IP:         %s%s", wifi_IP, wifi_mask);
    mvwprintw(header, 3, 1, " Gateway:    %s", gateway_default);
    wattroff(header, A_BOLD);
    wrefresh(header);

}

int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord)
{
    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;

    *height_win = *height / 2;
    if (*height_win < 15) {
        *height_win = 15;
    }

    *width_win = *width / 2;
    if (*width_win < 33) {
        *width_win = 33;
    }

    *height_x = (*height - *height_win) / 2;
    *width_y = (*width - *width_win) / 2;
}