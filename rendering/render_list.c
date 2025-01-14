#include "../header.h"


int render_list(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *list, _Bool *active, char list_wifi[][INT_64], _Bool bool_render_list)
{   
    if (bool_render_list) {
        take_list_wifi(ptr_wifi_data, coord, list_wifi);
    }

    char new_list_wifi[NUM_WIFI_LIST][MAX_LINE] = {0};
    int *cur_list = &coord->cur_list;
    int *offset = &coord->offset;
    int *height_list = &coord->height_list;
    int *width_list = &coord->width_list;
    int *visible_lines = &coord->visible_lines;
    int full_lines = coord->full_lines;
    _Bool header_or_list = 1;
    getmaxyx(list, *height_list, *width_list);
    *visible_lines = *height_list - 2 < full_lines ? *height_list - 2 : full_lines;

    add_empty_line(ptr_wifi_data, coord, list_wifi, full_lines, new_list_wifi, header_or_list);

    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    *active ? wbkgd(list, COLOR_PAIR(1)) : wbkgd(list, COLOR_PAIR(13));

    // for (int i = 0, j = 1; i < *height_list - 2; ++i, ++j) {
    //     mvwprintw(list, j, 1, "%-*s", *width_list - 2, "");
    // }
    if (new_list_wifi[0] != 0) {
        for (int i = 0, j = 1; i < *visible_lines; ++i, ++j) {
            wattron(list, A_BOLD);
            if (*cur_list == j) {
                wattron(list, COLOR_PAIR(2));
                mvwprintw(list, j, 1, "%s", new_list_wifi[i + *offset]);
                wattroff(list, COLOR_PAIR(2));
            } else {
                mvwprintw(list, j, 1, "%s", new_list_wifi[i + *offset]);
            }
            wattroff(list, A_BOLD);
        }
    }

    wrefresh(list);
}