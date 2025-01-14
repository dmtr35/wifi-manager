#include "../../header.h"

int enter_menu(wifi_data *ptr_wifi_data, data_wifi_menu *wifi_menu)
{
    char wifi_pass[INT_64];
    int *cur_menu = &wifi_menu->cur_menu;
    char *wifi_name = wifi_menu->wifi_name;
    char *wifi_interface = ptr_wifi_data->wifi_interface;

    switch (*cur_menu) {
    case 2:
        if (wifi_name[0] == '*') {
            del_wifi_proc(wifi_interface);
            wifi_name++;
            get_pass(wifi_name, wifi_pass);
            set_connect(ptr_wifi_data, wifi_name, wifi_pass);
        }
        break;
    case 3:
        render_create_config(ptr_wifi_data, wifi_menu);
        break;
    case 4:
        del_wifi_proc(wifi_interface);
        break;
    }
    return 0;
}

