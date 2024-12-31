#include "header.h"


WINDOW *header, *list, *frame;


int main()
{
    setlocale(LC_ALL, "");
    initscr();                                  // инициализация ncurses
    // nodelay(stdscr, TRUE);                      // блокирующий режим
    noecho();                                   // Отключаем вывод введенных символов
    cbreak();
    keypad(stdscr, TRUE);                       // Включаем обработку функциональных клавиш
    curs_set(0);

    int ch;
    _Bool active = false;
    wifi_data *ptr_wifi_data = malloc(sizeof(wifi_data));
    coord_win *coord = malloc(sizeof(coord_win));
    char **list_wifi = malloc(NUM_WIFI_LIST * sizeof(char *));
    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        list_wifi[i] = malloc(MAX_LEN * sizeof(char));
    }

    int *cur_header = &coord->cur_header;
    int *cur_list = &coord->cur_list;
    int *offset = &coord->offset;
    int *height_header = &coord->height_header;
    int *width_header = &coord->width_header;
    int *height_list = &coord->height_list;
    int *width_list = &coord->width_list;
    int *visible_lines = &coord->visible_lines;
    int *full_lines = &coord->full_lines;
    _Bool *bool_render_list = &coord->bool_render_list;

    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;
    int *wifi_status = &ptr_wifi_data->wifi_status;
    *cur_header = 1;
    *cur_list = 1;
    *offset = 0;
    *bool_render_list = true;


    wifi_dev(ptr_wifi_data);
    wifi_info(ptr_wifi_data);


    while (1) {
        getmaxyx(stdscr, *height, *width);
        calculate_coord_win(ptr_wifi_data, coord);
        header = newwin(6, *width_win, *height_x, *width_y);
        wborder(header, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        keypad(header, TRUE);

        list = newwin(*height_win - 7, *width_win, *height_x+6, *width_y);
        wborder(list, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        keypad(list, TRUE);

        getmaxyx(header, *height_header, *width_header);
        getmaxyx(list, *height_list, *width_list);

        render_header(ptr_wifi_data, coord, header, &active);
        render_list(ptr_wifi_data, coord, list, &active, list_wifi, *bool_render_list);
        *bool_render_list = false;

        if (!active) {
            ch = wgetch(header);
            switch (ch) {
            case KEY_UP:
                if (*cur_header > 1) {
                    (*cur_header)--;
                } else if (*cur_header == 1) {
                    *cur_header = 4;
                }
                break;
            case KEY_DOWN:
                if (*cur_header < 4) {
                    (*cur_header)++;
                } else if (*cur_header == 4) {
                    *cur_header = 1;
                }
                break;
            case '\n':
                enter_header(ptr_wifi_data, coord);
                break;
            }
        } else {
            ch = wgetch(list);

            switch (ch) {
            case KEY_UP:
                if (*cur_list > 1) {
                    (*cur_list)--;
                } else if (*cur_list == 1 && *offset > 0) {
                    (*offset)--;
                }
                break;
            case KEY_DOWN:
                if (*cur_list < *visible_lines) {
                    (*cur_list)++;
                } else if (*cur_list == *visible_lines && *offset < (*full_lines - *visible_lines)) {
                    (*offset)++;
                }
                break;
            case '\n':
                enter_list(ptr_wifi_data, coord, list_wifi);
                break;
            }
        }

        if (ch == 27) {                                                 // ESC
            break;
        }
        if (ch == 9) {                                                  // TAB
            active = !active;
            if (*wifi_status == 1) {
                render_list(ptr_wifi_data, coord, list, &active, list_wifi, true);
            }
        }
        else if (ch == 'r' || ch == KEY_RESIZE) {
            int new_height, new_width;
            getmaxyx(stdscr, new_height, new_width);
            if (new_height != *height || new_width != *width) {
                clear();
                refresh();
                *height = new_height;
                *width = new_width;
                calculate_coord_win(ptr_wifi_data, coord);
            }
        }
    }


    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        free(list_wifi[i]);
    }
    free(list_wifi);
    free(ptr_wifi_data);
    free(coord);
    endwin();
    return 0;
}

