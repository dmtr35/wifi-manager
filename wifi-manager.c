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
    wifi_data *ptr_wifi_data = malloc(sizeof(wifi_data));
    coord_win *coord = malloc(sizeof(coord_win));
    char **list_wifi = malloc(NUM_WIFI_LIST * sizeof(char *));
    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        list_wifi[i] = malloc(MAX_LEN * sizeof(char));
    }

    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;
    char *wifi_status = ptr_wifi_data->wifi_status;

    wifi_dev(ptr_wifi_data);
    wifi_info(ptr_wifi_data);
    if (strcmp(wifi_status, "UP") == 0) {
        take_list_wifi(ptr_wifi_data, list_wifi);
    }

    getmaxyx(stdscr, *height, *width);
    calculate_coord_win(ptr_wifi_data, coord);
    frame = newwin(*height_win, *width_win, *height_x, *width_y);
    mvwhline(frame, 5, 0, ACS_HLINE, *width_win);
    box(frame, 0, 0);
    wrefresh(frame);

    header = newwin(4, *width_win-2, *height_x+1, *width_y+1);
    // box(header, 0, 0);
    // wrefresh(header);

    list = newwin(*height_win - 7, *width_win-2, *height_x+6, *width_y+1);
    scrollok(list, TRUE);
    // box(list, 0, 0);
    // wrefresh(list);


    

    
    // while (1) {
        // render_main(ptr_wifi_data, coord, header, list);

        ch = wgetch(header);

    // }
    
    
    endwin();
    return 0;
}

