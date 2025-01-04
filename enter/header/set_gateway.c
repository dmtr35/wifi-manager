#include "../../header.h"

int set_gateway(wifi_data *ptr_wifi_data, coord_win *coord)
{
    WINDOW *win_gateway;
    int ch;
    char buffer_gateway[16] = {0};
    int buffer_pos = 0;
    int max_buf = 15;
    const char *pattern_gateway = "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$";

    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;

    win_gateway = newwin(1, *width_win - 15, *height_x + 4, *width_y + 14);

    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(10, COLOR_WHITE, COLOR_GREEN);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    wbkgd(win_gateway, COLOR_PAIR(10));

    while (1) {
        ch = wgetch(win_gateway);

        if (ch == '\n') {
            if (validate_input(buffer_gateway, pattern_gateway)) {
                change_gateway(ptr_wifi_data, buffer_gateway);
                break;
            } else {
                break;
            }
        }
        else if (ch == KEY_BACKSPACE || ch == 127) {
            delete_char_from_enter(win_gateway, buffer_gateway, &buffer_pos);
        } else if (ch > 45 && ch < 58) {
            add_char_to_enter(win_gateway, ch, max_buf, buffer_gateway, &buffer_pos);
        }

        wrefresh(win_gateway);
    }
}




