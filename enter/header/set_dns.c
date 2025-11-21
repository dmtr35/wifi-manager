#include "../../header.h"

int set_dns(wifi_data *ptr_wifi_data, coord_win *coord)
{
    WINDOW *win_dns;
    int ch;
    char buffer_dns[16] = {0};
    int buffer_pos = 0;
    int max_buf = 15;
    const char *pattern_dns = "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$";

    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;

    win_dns = newwin(1, *width_win - 15, *height_x + 5, *width_y + 14);

    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(10, COLOR_WHITE, COLOR_GREEN);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    wbkgd(win_dns, COLOR_PAIR(10));

    while (1) {
        ch = wgetch(win_dns);

        if (ch == '\n') {
            if (validate_input(buffer_dns, pattern_dns)) {
                change_dns(buffer_dns);
                break;
            } else {
                break;
            }
        }
        else if (ch == KEY_BACKSPACE || ch == 127) {
            delete_char_from_enter(win_dns, buffer_dns, &buffer_pos);
        } else if (ch > 45 && ch < 58 && ch != 47) {
            add_char_to_enter(win_dns, ch, max_buf, buffer_dns, &buffer_pos);
        }

        wrefresh(win_dns);
    }
}




