#include "../../header.h"


int enter_header(wifi_data *ptr_wifi_data, coord_win *coord)
{
    int *cur_header = &coord->cur_header;
    int *cur_list = &coord->cur_list;
    int *full_lines = &coord->full_lines;
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    char *gateway_default = ptr_wifi_data->gateway_default;
    int *wifi_status = &ptr_wifi_data->wifi_status;
    _Bool *bool_render_list = &coord->bool_render_list;

    switch (*cur_header) {
    case 2:
        set_interface_state(wifi_interface, !*wifi_status);
        wifi_info(ptr_wifi_data);
        if (*wifi_status == 1) {
            *bool_render_list = true;
        }
        *cur_list = 1;
        *full_lines = 0;
        break;
    case 3:
        set_ip(ptr_wifi_data, coord);
        wifi_info(ptr_wifi_data);
        break;
    case 4:
        set_gateway(ptr_wifi_data, coord);
        wifi_info(ptr_wifi_data);
        break;
    }
    return 0;
}



int set_interface_state(const char *wifi_interface, int state) {
    int sock;
    struct ifreq ifr;

    // Создаём сокет для управления интерфейсом
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    // Указываем имя интерфейса
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, wifi_interface, IFNAMSIZ - 1);

    // Получаем текущие флаги интерфейса
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0) {
        perror("ioctl(SIOCGIFFLAGS)");
        close(sock);
        return 1;
    }

    // Меняем состояние интерфейса
    if (state) {
        ifr.ifr_flags |= IFF_UP;  // Включаем
    } else {
        ifr.ifr_flags &= ~IFF_UP; // Выключаем
    }

    // Устанавливаем новые флаги интерфейса
    if (ioctl(sock, SIOCSIFFLAGS, &ifr) < 0) {
        perror("ioctl(SIOCSIFFLAGS)");
    }

    sleep(1);
    close(sock);
}