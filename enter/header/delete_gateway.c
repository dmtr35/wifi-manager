#include "../../header.h"


int delete_gateway(wifi_data *ptr_wifi_data)
{
    char *gateway_default = ptr_wifi_data->gateway_default;
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
    addr->sin_addr.s_addr = inet_addr(gateway_default);               // текущий gateway

    addr = (struct sockaddr_in *)&route.rt_dst;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;                             // Для default route

    addr = (struct sockaddr_in *)&route.rt_genmask;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;                             // Маска default

    route.rt_flags = RTF_UP | RTF_GATEWAY;

    // Удаляем маршрут
    if ((err = ioctl(sockfd, SIOCDELRT, &route)) != 0) {
        // perror("SIOCDELRT failed");
        // close(sockfd);
        // exit(1);
    }

    close(sockfd);
    return 0;
}