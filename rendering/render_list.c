#include "../header.h"


int render_list(wifi_data *ptr_wifi_data, coord_win *coord, cursor *curs, WINDOW *list, _Bool *active, char **list_wifi)
{

    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    *active ? wbkgd(list, COLOR_PAIR(1)) : wbkgd(list, COLOR_PAIR(13));





    wrefresh(list);
    printf("\n");
}