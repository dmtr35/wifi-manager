#include "../../header.h"



int enter_list(wifi_data *ptr_wifi_data, coord_win *coord, char list_wifi[][INT_64])
{

    WINDOW *win_menu;
    int ch;
    char fields[3][14] = {0};
    strcpy(fields[0], "connect");
    strcpy(fields[1], "create config");
    strcpy(fields[2], "disconnect");

    
    int *cur_list = &coord->cur_list;
    int *offset = &coord->offset;
    int number_list = *cur_list + *offset;

    int *height_list = &coord->height_list;
    int *width_list = &coord->width_list;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;
    int height_menu_x = *height_x + 6 + (*height_list - 5) / 2;
    int width_menu_y = *width_y + (*width_list - 25) / 2;
    char *wifi_name = list_wifi[number_list-1];
    int coord_titel_name = (30 - strlen(wifi_name)) / 2;
    
    data_wifi_menu wifi_menu;
    wifi_menu.cur_menu = 2;
    wifi_menu.height_menu_x = height_menu_x;
    wifi_menu.width_menu_y = width_menu_y;
    wifi_menu.wifi_name = wifi_name;

    int *cur_menu = &wifi_menu.cur_menu;

    win_menu = newwin(6, 30, height_menu_x, width_menu_y);
    wborder(win_menu, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    keypad(win_menu, TRUE);



    start_color();
    init_pair(14, COLOR_WHITE, COLOR_GREEN);
    wbkgd(win_menu, COLOR_PAIR(14));

    wattron(win_menu, A_BOLD);
    mvwprintw(win_menu, 0, coord_titel_name, "%s", wifi_name);
    wattroff(win_menu, A_BOLD);

    while (1) {
        for (int i = 0, j = 2; i < 3; ++i, ++j) {
            wattron(win_menu, A_BOLD);
            if (*cur_menu == j) {
                wattron(win_menu, COLOR_PAIR(2));
                mvwprintw(win_menu, j, (30 - strlen(fields[i])) / 2, "%s", fields[i]);
                wattroff(win_menu, COLOR_PAIR(2));
            } else {
                mvwprintw(win_menu, j, (30 - strlen(fields[i])) / 2, "%s", fields[i]);
            }
            wattroff(win_menu, A_BOLD);
        }

        ch = wgetch(win_menu);

        switch (ch) {
            case KEY_UP:
                if (*cur_menu > 2) {
                    (*cur_menu)--;
                }
                break;
            case KEY_DOWN:
                if (*cur_menu < 4) {
                    (*cur_menu)++;
                }
                break;
            case '\n':
                enter_menu(ptr_wifi_data, &wifi_menu);
                ch = 27;
                break;
            }

        if (ch == 27) {                                                 // ESC
            break;
        }
    }
}

