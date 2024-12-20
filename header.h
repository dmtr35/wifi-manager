#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/wireless.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ncurses.h>
#include <locale.h>

// #define ESCDELAY = 500;
#define NUM_WIFI_LIST 30
#define MAX_LEN 64
#define INT_64 64
#define SIZE_BUFF 1024
#define ADDR_LEN 16
#define COLOR_GREY 8

typedef struct wifi_data {
    char wifi_interface[INT_64];
    int wifi_status;
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

    int cur_header;
    int cur_list;

    int height_list;
    int width_list;
    int offset;

    int visible_lines;
    int full_lines;
} coord_win;

typedef struct cursor {
    int pid_proc;
} cursor;



// rendering/render_header.c
int render_header(wifi_data *ptr_wifi_data, coord_win *coord, cursor *curs, WINDOW *header, _Bool *active);
int form_header(wifi_data *ptr_wifi_data, coord_win *coord, char fields[][256]);

// rendering/render_list.c
int render_list(wifi_data *ptr_wifi_data, coord_win *coord, cursor *curs, WINDOW *list, _Bool *active, char **list_wifi);

// wifi_dev.c
int wifi_dev(wifi_data *ptr_wifi_data);
int wifi_info(wifi_data *ptr_wifi_data);
// take_wifi_list.c
int take_list_wifi(wifi_data *ptr_wifi_data, coord_win *coord, char **list_wifi);


// extra_func/extra_func.c
int netmask_to_cidr();
int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord);
void create_empty_line(char empty_line, int count);




#endif



