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
    // _Bool active = true;
    _Bool active = false;
    wifi_data *ptr_wifi_data = malloc(sizeof(wifi_data));
    coord_win *coord = malloc(sizeof(coord_win));
    cursor *curs = malloc(sizeof(cursor));
    char **list_wifi = malloc(NUM_WIFI_LIST * sizeof(char *));
    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        list_wifi[i] = malloc(MAX_LEN * sizeof(char));
    }
    
    // int *pid_proc = &curs->pid_proc;

    int *cur_header = &coord->cur_header;
    int *cur_list = &coord->cur_list;
    int *offset = &coord->offset;
    int *height_list = &coord->height_list;
    int *width_list = &coord->width_list;
    int *visible_lines = &coord->visible_lines;
    int *full_lines = &coord->full_lines;

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

    getmaxyx(stdscr, *height, *width);
    calculate_coord_win(ptr_wifi_data, coord);
    getmaxyx(list, *height_list, *width_list);

    header = newwin(6, *width_win, *height_x, *width_y);
    wborder(header, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    keypad(header, TRUE);

    list = newwin(*height_win - 7, *width_win, *height_x+6, *width_y);
    wborder(list, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    keypad(list, TRUE);
    scrollok(list, TRUE);


    wifi_dev(ptr_wifi_data);
    wifi_info(ptr_wifi_data);


    if (*wifi_status == 0) {
        take_list_wifi(ptr_wifi_data, coord, list_wifi);
        render_list(ptr_wifi_data, coord, curs, list, &active, list_wifi);
    }

    
    while (1) {
        // if (*pid_proc > 0) {
        //     kill(*pid_proc, 9);
        // }
        render_header(ptr_wifi_data, coord, curs, header, &active);
        if (*wifi_status == 0) {
            render_list(ptr_wifi_data, coord, curs, list, &active, list_wifi);
        }

        if (active) {
            ch = wgetch(list);
            // getmaxyx(list, height_list, width_list);

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
                wprintw(header, "Enter нажата\n");
                break;
            }
        } else{
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
                wprintw(header, "Enter нажата\n");
                break;
            }
        }

        if (ch == 27) {                                                 // ESC
            break;
        }
        if (ch == 9) {                                                  // TAB
            active = !active;
        }
    }


    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        free(list_wifi[i]);
    }
    free(list_wifi);
    free(ptr_wifi_data);
    free(coord);
    free(curs);
    endwin();
    return 0;
}

