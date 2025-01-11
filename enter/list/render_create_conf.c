#include "../../header.h"


int render_create_config(wifi_data *ptr_wifi_data, data_wifi_menu *wifi_menu)
{
    WINDOW *win_pass;
    int ch;
    char buffer_pass[INT_64] = {0};
    int buffer_pos = 0;
    int max_buf = 64;
    const char *pattern_pass = "^[a-zA-Z0-9@$!%*?&]{8,63}$";


    int *cur_menu = &wifi_menu->cur_menu;
    int *height_menu_x = &wifi_menu->height_menu_x;
    int *width_menu_y = &wifi_menu->width_menu_y;
    char *wifi_name = wifi_menu->wifi_name;

    win_pass = newwin(1, 28, *height_menu_x + 3, *width_menu_y + 1);
    start_color();
    init_pair(15, COLOR_WHITE, COLOR_BLACK);
    wbkgd(win_pass, COLOR_PAIR(15));


    while (1) {
        ch = wgetch(win_pass);

        if (ch == '\n') {
            if (validate_input(buffer_pass, pattern_pass)) {
                set_create_conf(ptr_wifi_data, wifi_name, buffer_pass);
                break;
            } else {
                break;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            delete_char_from_enter(win_pass, buffer_pass, &buffer_pos);
        } else if (ch > 20 && ch < 127) {
            add_char_to_enter(win_pass, ch, max_buf, buffer_pass, &buffer_pos);
        }


        wrefresh(win_pass);
    }

    return 0;
}