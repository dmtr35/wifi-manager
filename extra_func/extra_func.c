#include "../header.h"
// 255.255.255.0
// преобразование маски подсети в вид cidr (/24)
int netmask_to_cidr(const char *netmask)
{
    char netmask_copy[16];
    strncpy(netmask_copy, netmask, sizeof(netmask_copy) - 1);
    netmask_copy[sizeof(netmask_copy) - 1] = '\0'; // Безопасный конец строки

    uint32_t mask;
    int cidr = 0;

    char *ptr = strtok(netmask_copy, ".");
    while (ptr != NULL) {
        mask = atoi(ptr);

        // Подсчёт установленных битов в байте
        while (mask) {
            cidr += mask & 1;
            mask >>= 1;
        }

        ptr = strtok(NULL, ".");
    }

    return cidr;
}

// высчитываем кооодинаты окон
int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord)
{
    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;

    *height_win = *height / 2;
    if (*height_win < 15) {
        *height_win = 15;
    }

    *width_win = *width / 2;
    if (*width_win < 33) {
        *width_win = 33;
    }

    *height_x = (*height - *height_win) / 2;
    *width_y = (*width - *width_win) / 2;
}

