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
    _Bool active = true;
    // _Bool active = false;
    wifi_data *ptr_wifi_data = malloc(sizeof(wifi_data));
    coord_win *coord = malloc(sizeof(coord_win));
    cursor *curs = malloc(sizeof(cursor));
    char **list_wifi = malloc(NUM_WIFI_LIST * sizeof(char *));
    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        list_wifi[i] = malloc(MAX_LEN * sizeof(char));
    }

    int *cur_header = &curs->cur_header;
    int *cur_list = &curs->cur_list;
    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;
    int *wifi_status = &ptr_wifi_data->wifi_status;

    *cur_header = 1;
    *cur_list = 1;

    wifi_dev(ptr_wifi_data);
    wifi_info(ptr_wifi_data);
    if (wifi_status == 0) {
        take_list_wifi(ptr_wifi_data, list_wifi);
    }

    getmaxyx(stdscr, *height, *width);
    calculate_coord_win(ptr_wifi_data, coord);

    header = newwin(6, *width_win, *height_x, *width_y);
    wborder(header, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    keypad(header, TRUE);

    list = newwin(*height_win - 7, *width_win, *height_x+6, *width_y);
    wborder(list, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    keypad(list, TRUE);
    scrollok(list, TRUE);

    

    
    while (1) {
        render_header(ptr_wifi_data, coord, curs, header, &active);
        render_list(ptr_wifi_data, coord, curs, list, &active, list_wifi);

        if (active) {
            ch = wgetch(list);
            switch (ch) {
            case KEY_UP:
                printw("Стрелка вверх\n");
                break;
            case KEY_DOWN:
                printw("Стрелка вниз\n");
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

