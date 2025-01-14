#include "../../header.h"

int change_gateway(wifi_data *ptr_wifi_data, char *buffer_gateway) {
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    char gateway_ip[16] = {0};
    strcpy(gateway_ip, buffer_gateway);

    delete_gateway(ptr_wifi_data);

    int sockfd;
    struct rtentry route;
    struct sockaddr_in *addr;
    int err = 0;

    // create the socket
    if (((sockfd = socket(AF_INET, SOCK_DGRAM, 0))) < 0) {
        // perror("socket");
        exit(1);
    }

    memset(&route, 0, sizeof(route));
    addr = (struct sockaddr_in *)&route.rt_gateway;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(gateway_ip);

    addr = (struct sockaddr_in *)&route.rt_dst;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;

    addr = (struct sockaddr_in *)&route.rt_genmask;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;

    route.rt_flags = RTF_UP | RTF_GATEWAY;

    // добавляем маршрут
    if ((err = ioctl(sockfd, SIOCADDRT, &route)) != 0) {
        // perror("SIOCADDRT failed");
        // close(sockfd);
        // exit(1);
    }

    close(sockfd);
    return 0;
}