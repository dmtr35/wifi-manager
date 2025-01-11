#include "../../header.h"

int enter_menu(wifi_data *ptr_wifi_data, data_wifi_menu *wifi_menu)
{
    char wifi_pass[INT_64];
    int *cur_menu = &wifi_menu->cur_menu;
    // int *height_menu_x = &wifi_menu->height_menu_x;
    // int *width_menu_y = &wifi_menu->width_menu_y;
    char *wifi_name = wifi_menu->wifi_name;
    // int *cur_list = &coord->cur_list;
    // int *full_lines = &coord->full_lines;
    // char *wifi_interface = ptr_wifi_data->wifi_interface;
    // char *gateway_default = ptr_wifi_data->gateway_default;
    // int *wifi_status = &ptr_wifi_data->wifi_status;
    // int *count_ifaces = &ptr_wifi_data->count_ifaces;
    // _Bool *bool_render_list = &coord->bool_render_list;
    // char (*ifaces)[INT_32] = ptr_wifi_data->ifaces;

    switch (*cur_menu) {
    case 2:
        if (wifi_name[0] == '*') {
            wifi_name++;
            get_pass(wifi_name, wifi_pass);
            set_connect(ptr_wifi_data, wifi_name, wifi_pass);
        }
        break;
    case 3:
        render_create_config(ptr_wifi_data, wifi_menu);
        break;
    case 4:
        break;
    }
    return 0;
}

