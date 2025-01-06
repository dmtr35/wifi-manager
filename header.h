#ifndef FUNC_H
#define FUNC_H
#define _GNU_SOURCE
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
#include <pthread.h>
#include <sys/un.h>
#include <ctype.h>
#include <regex.h>
#include <linux/route.h>


#include <ncurses.h>
#include <locale.h>

#define NUM_WIFI_LIST 30
#define MAX_LEN 64
#define INT_64 64
#define INT_32 32
#define SIZE_BUFF 64
#define ADDR_LEN 16
#define COLOR_GREY 8


typedef struct wifi_data {
    int wifi_status;
    int count_ifaces;
    char wifi_IP[ADDR_LEN];
    char ifaces[5][INT_32];
    char wifi_interface[INT_64];
    char wifi_mask_cidr[INT_64];
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

    int height_header;
    int width_header;

    int height_list;
    int width_list;
    int offset;

    int visible_lines;
    int full_lines;

    _Bool bool_render_list;
} coord_win;





// rendering/render_header.c
int render_header(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *header, _Bool *active);
int form_header(wifi_data *ptr_wifi_data, coord_win *coord, char fields[][256]);

// rendering/render_list.c
int render_list(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *list, _Bool *active, char **list_wifi, _Bool tab);

// wifi_dev.c
int wifi_dev(wifi_data *ptr_wifi_data);
int wifi_info(wifi_data *ptr_wifi_data);
// take_wifi_list.c
int take_list_wifi(wifi_data *ptr_wifi_data, coord_win *coord, char **list_wifi);
// int* take_list_wifi(int *arg);


// extra_func/extra_func.c
int netmask_to_cidr();
int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord);
int create_empty_line(char empty_line, int count);
int validate_input(const char *ip, const char *pattern_ip);
int cidr_to_netmask(char *mask, char *wifi_mask);
void del_wifi_proc(char *interface);
void iface_down(char *interface);
void iface_up(char *interface);

// enter/header/enter_header.c
int enter_header(wifi_data *ptr_wifi_data, coord_win *coord);
int set_interface_state(const char *wifi_interface, int state);
// enter/header/set_ip.c
int set_ip(wifi_data *ptr_wifi_data, coord_win *coord);
int set_ip_address(wifi_data *ptr_wifi_data, char *buffer_ip);
// enter/header/set_gateway.c
int set_gateway(wifi_data *ptr_wifi_data, coord_win *coord);
int change_gateway(wifi_data *ptr_wifi_data, char *buffer_gateway);
int delete_gateway(wifi_data *ptr_wifi_data);

// enter/list/enter_list.c
int enter_list(wifi_data *ptr_wifi_data, coord_win *coord, char **list_wifi);
// enter/list/set_connect.c
int set_connect(wifi_data *ptr_wifi_data, char *wifi_name, char *buffer_pass);

// command_line/buffer_save.c
int add_char_to_enter(WINDOW *win, int ch, int max_buf, char *buffer_ip, int *buffer_pos);
int delete_char_from_enter(WINDOW *win, char *buffer_ip, int *buffer_pos);

#endif



