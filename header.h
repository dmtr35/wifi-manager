#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/wireless.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ncurses.h>
#include <locale.h>

#define NUM_WIFI_LIST 30
#define MAX_LEN 64
#define INT_64 64
#define SIZE_BUFF 1024
#define ADDR_LEN 16

typedef struct wifi_data {
    char wifi_interface[INT_64];
    char wifi_status[INT_64];
    char wifi_IP[ADDR_LEN];
    char wifi_mask[INT_64];
    char gateway_default[INT_64];
} wifi_data;

typedef struct coord_win {
    int width;
    int height;
    int height_win;
    int width_win;
    int height_x;
    int width_y;
} coord_win;

// typedef struct list_wifi {
//     char SSID[INT_64];
// } list_wifi;


// rendefing/render_main.c
int render_main(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *header, WINDOW *list);
int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord);


// wifi_dev.c
int wifi_dev(wifi_data *ptr_wifi_data);
int wifi_info(wifi_data *ptr_wifi_data);
// take_wifi_list.c
int take_list_wifi(wifi_data *ptr_wifi_data, char **list_wifi);


// extra_func/extra_func.c
int netmask_to_cidr();





#endif



