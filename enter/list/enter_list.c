#include "../../header.h"

int enter_list(wifi_data *ptr_wifi_data, coord_win *coord, char **list_wifi)
{
    WINDOW *win_ip;
    int ch;
    char buffer_pass[MAX_LEN] = {0};
    int buffer_pos = 0;
    int max_buf = 64;
    const char *pattern_pass = "^[a-zA-Z0-9@$!%*?&]{8,63}$";


    int *cur_list = &coord->cur_list;
    int *offset = &coord->offset;
    int number_list = *cur_list + *offset;

    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;
    win_ip = newwin(1, *width_win - 15, *height_x + 6 + number_list, *width_y + 14);

    char *wifi_name = list_wifi[number_list-1];

    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(10, COLOR_WHITE, COLOR_GREEN);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    wbkgd(win_ip, COLOR_PAIR(10));

    while (1) {
        ch = wgetch(win_ip);

        if (ch == '\n') {
            if (validate_input(buffer_pass, pattern_pass)) {
                set_connect(ptr_wifi_data, wifi_name, buffer_pass);
                break;
            } else {
                break;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            delete_char_from_enter(win_ip, buffer_pass, &buffer_pos);
        } else if (ch > 20 && ch < 127) {
            add_char_to_enter(win_ip, ch, max_buf, buffer_pass, &buffer_pos);
        }

        wrefresh(win_ip);
    }
}

