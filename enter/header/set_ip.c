#include "../../header.h"


void set_ip(wifi_data *ptr_wifi_data, coord_win *coord)
{
    WINDOW *win_ip;
    int ch;
    char buffer_ip[19] = {0};
    int buffer_pos = 0;
    const char *pattern_ip = "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])/(3[0-2]|[1-2]?[0-9])$";

    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;

    win_ip = newwin(1, *width_win - 15, *height_x + 3, *width_y + 14);

    start_color();
    init_color(COLOR_GREY, 300, 300, 300);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREY);
    init_pair(10, COLOR_WHITE, COLOR_GREEN);
    init_pair(13, COLOR_WHITE, COLOR_GREY);
    wbkgd(win_ip, COLOR_PAIR(10));

    while (1) {
        ch = wgetch(win_ip);

        if (ch == '\n') {
            if (validate_ip_mask(buffer_ip, pattern_ip)) {
                set_ip_address(ptr_wifi_data, buffer_ip);
                break;
            } else {
                break;
            }
        }
        else if (ch == KEY_BACKSPACE || ch == 127) {
            delete_char_from_enter_name(win_ip, buffer_ip, &buffer_pos);
        } else if (ch > 45 && ch < 58) {
            add_char_to_enter_name(win_ip, ch, buffer_ip, &buffer_pos);
        }

        wrefresh(win_ip);
    }
    wifi_info(ptr_wifi_data);
}


int set_ip_address(wifi_data *ptr_wifi_data, char *buffer_ip) {
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    char wifi_IP[16] = {0};
    char wifi_mask[16] = {0};

    strcpy(wifi_IP, buffer_ip);
    char *slash = strchr(wifi_IP, '/');
    *slash = '\0';
    char *mask_cidr = slash + 1;
    cidr_to_netmask(mask_cidr, wifi_mask);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct ifreq ifr;
    struct sockaddr_in *addr;

    // Устанавливаем интерфейс
    strncpy(ifr.ifr_name, wifi_interface, IFNAMSIZ);

    // Устанавливаем IP
    addr = (struct sockaddr_in *)&ifr.ifr_addr;
    addr->sin_family = AF_INET;
    if (inet_pton(AF_INET, wifi_IP, &addr->sin_addr) <= 0) {
        perror("Invalid IP address format");
        close(fd);
        return -1;
    }

    if (ioctl(fd, SIOCSIFADDR, &ifr) < 0) {
        perror("Failed to set IP address");
        close(fd);
        return -1;
    }

    // Устанавливаем маску подсети
    addr = (struct sockaddr_in *)&ifr.ifr_netmask;
    addr->sin_family = AF_INET;
    if (inet_pton(AF_INET, wifi_mask, &addr->sin_addr) <= 0) {
        perror("Invalid netmask format");
        close(fd);
        return -1;
    }

    if (ioctl(fd, SIOCSIFNETMASK, &ifr) < 0) {
        perror("Failed to set netmask");
        close(fd);
        return -1;
    }

    // Включаем интерфейс (если он не включен)
    if (ioctl(fd, SIOCSIFFLAGS, &ifr) < 0) {
        perror("Failed to bring up interface");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}