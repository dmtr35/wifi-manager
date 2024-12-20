#include "../header.h"


int render_list(wifi_data *ptr_wifi_data, coord_win *coord, cursor *curs, WINDOW *list, _Bool *active, char **list_wifi)
{
    int *cur_list = &coord->cur_list;
    int *offset = &coord->offset;
    int *height_list = &coord->height_list;
    int *width_list = &coord->width_list;
    int *visible_lines = &coord->visible_lines;
    int *full_lines = &coord->full_lines;
    // int *pid_proc = &curs->pid_proc;

    getmaxyx(list, *height_list, *width_list);
    *visible_lines = *height_list - 2 < *full_lines ? *height_list - 2 : *full_lines;

    // int pid = fork();
    // if (pid < 0) {
    //     perror("Error fork");
    //     return 1;
    // }

    // if (pid == 0) {                                            // Дочерний процесс
        // while (1) {
            // take_list_wifi(ptr_wifi_data, coord, list_wifi);


            start_color();
            init_color(COLOR_GREY, 300, 300, 300);
            init_pair(1, COLOR_WHITE, COLOR_BLUE);
            init_pair(2, COLOR_WHITE, COLOR_GREY);
            init_pair(13, COLOR_WHITE, COLOR_GREY);
            *active ? wbkgd(list, COLOR_PAIR(1)) : wbkgd(list, COLOR_PAIR(13));

            for (int i = 0, j = 1; i < *visible_lines && i < *full_lines; ++i, ++j) {
                wattron(list, A_BOLD);
                mvwprintw(list, j, 1, "%-*s", *width_list - 2, "");
                if (*cur_list == j) {
                    wattron(list, COLOR_PAIR(2));
                    mvwprintw(list, j, 1, " %s", list_wifi[i + *offset]);
                    wattroff(list, COLOR_PAIR(2));
                } else {
                    mvwprintw(list, j, 1, " %s", list_wifi[i + *offset]);
                }
                wattroff(list, A_BOLD);
            }

            wrefresh(list);
            printf("\n");
            // sleep(10);
        // }
    // }
    // *pid_proc = pid;
    printf("\n");
}