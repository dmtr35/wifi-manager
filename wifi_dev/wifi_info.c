#include "../header.h"

int wifi_dev(wifi_data *ptr_wifi_data)
{
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    struct if_nameindex *interfaces, *iface;
    struct ifreq ifr;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    interfaces = if_nameindex();
    if (!interfaces) {
        perror("if_nameindex");
        close(sockfd);
        return 1;
    }

    for (iface = interfaces; iface->if_name != NULL; iface++) {
        memset(&ifr, 0, sizeof(ifr));
        strncpy(ifr.ifr_name, iface->if_name, IFNAMSIZ - 1);

        if (ioctl(sockfd, SIOCGIWNAME, &ifr) == 0) {
            strncpy(wifi_interface, iface->if_name, IFNAMSIZ - 1);
            break;
        } else {
            strcpy(wifi_interface, "not found");
        }
    }

    if_freenameindex(interfaces);
    close(sockfd);

    return 0;
}

int wifi_info(wifi_data *ptr_wifi_data)
{
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    int *wifi_status = &ptr_wifi_data->wifi_status;
    char *wifi_IP = ptr_wifi_data->wifi_IP;
    char *wifi_mask = ptr_wifi_data->wifi_mask;
    char *gateway_default = ptr_wifi_data->gateway_default;

    struct ifreq ifr;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, wifi_interface, IFNAMSIZ - 1);

    // Проверка статуса интерфейса
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) == 0) {
        if (ifr.ifr_flags & IFF_UP) {
            *wifi_status = 1;
        } else {
            *wifi_status = 0;
        }
    } else {
        perror("Ошибка получения флагов интерфейса");
    }

    // Получение IP-адреса
    if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0) {
        struct sockaddr_in *ipaddr = (struct sockaddr_in *)&ifr.ifr_addr;
        strcpy(wifi_IP, inet_ntoa(ipaddr->sin_addr));
    } else {
        perror("Ошибка получения IP-адреса");
    }

    // Получение маски подсети
    if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) == 0) {
        struct sockaddr_in *netmask = (struct sockaddr_in *)&ifr.ifr_netmask;
        int res = netmask_to_cidr(inet_ntoa(netmask->sin_addr));
        sprintf(wifi_mask, "/%d", res);
    } else {
        perror("Ошибка получения маски подсети");
    }

    // Получение шлюза по умолчанию
    FILE *route_file = fopen("/proc/net/route", "r");
    if (!route_file) {
        perror("Ошибка открытия /proc/net/route");
        close(sockfd);
        return 1;
    }

    char line[256];
    char iface[IFNAMSIZ];
    unsigned long dest, gateway;

    fgets(line, sizeof(line), route_file);              // Пропускаем заголовок

    while (fgets(line, sizeof(line), route_file)) {
        if (sscanf(line, "%s %lx %lx", iface, &dest, &gateway) == 3) {
            if (dest == 0) {
                struct in_addr gw_addr;
                gw_addr.s_addr = gateway;
                strncpy(gateway_default, inet_ntoa(gw_addr), INET_ADDRSTRLEN - 1);
                break;
            }
        }
    }

    close(sockfd);
    return 0;
}