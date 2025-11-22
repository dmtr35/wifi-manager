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
#include <dirent.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <locale.h>

#define NUM_WIFI_LIST 30
#define INT_64 64
#define INT_32 32
#define SIZE_BUFF 64
#define ADDR_LEN 16
#define COLOR_GREY 8
#define MAX_LINE 256

extern const char *path_supplicant;

typedef struct wifi_data {
    int wifi_status;
    int count_ifaces;
    char wifi_IP[ADDR_LEN];
    char ifaces[5][INT_32];
    char wifi_interface[INT_64];
    char wifi_mask_cidr[INT_64];
    char wifi_mask[INT_64];
    char gateway_default[INT_64];
    char dns[INT_32];
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

    int cur_menu;

    _Bool bool_render_list;
} coord_win;

typedef struct data_wifi_menu {
    int cur_menu;
    int height_menu_x; 
    int width_menu_y;
    char *wifi_name;
} data_wifi_menu;



// command_line/
int add_char_to_enter(WINDOW *win, int ch, int max_buf, char *buffer_ip, int *buffer_pos);
int delete_char_from_enter(WINDOW *win, char *buffer_ip, int *buffer_pos);

// enter/header/    -----------------------------------------------
int change_dns(char *buffer_dns);

int change_gateway(wifi_data *ptr_wifi_data, char *buffer_gateway);

int delete_gateway(wifi_data *ptr_wifi_data);

int enter_header(wifi_data *ptr_wifi_data, coord_win *coord);
int set_interface_state(const char *wifi_interface, int state);

int set_dns(wifi_data *ptr_wifi_data, coord_win *coord);

int set_gateway(wifi_data *ptr_wifi_data, coord_win *coord);

int set_ip(wifi_data *ptr_wifi_data, coord_win *coord);
int set_ip_address(wifi_data *ptr_wifi_data, char *buffer_ip);
int set_empty_address(wifi_data *ptr_wifi_data);
// ----------------------------------------------------------------



// enter/list/  ---------------------------------------------------
int enter_list(wifi_data *ptr_wifi_data, coord_win *coord, char list_wifi[][64]);

int enter_menu(wifi_data *ptr_wifi_data, data_wifi_menu *wifi_menu);

int render_create_config(wifi_data *ptr_wifi_data, data_wifi_menu *wifi_menu);

int set_connect(wifi_data *ptr_wifi_data, char *wifi_name, char *wifi_pass);

int set_create_conf(wifi_data *ptr_wifi_data, char *wifi_name, char *wifi_pass);
// ----------------------------------------------------------------



// extra_func/  ---------------------------------------------------
int netmask_to_cidr();
int cidr_to_netmask(char *mask, char *wifi_mask);
int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord);
int validate_input(const char *ip, const char *pattern_ip);
void del_wifi_proc(char *interface);
void iface_down(char *interface);
void iface_up(char *interface);
int check_connect(char *interface, char *result);
int check_config_file(char list_config[][INT_64]);
int get_pass(char *wifi_name, char *wifi_pass);

int add_empty_line(wifi_data *ptr_wifi_data, coord_win *coord, char list[][INT_64], int count_wifi_data_mod, char new_list[][MAX_LINE], _Bool header_or_list);
// int create_empty_line(char empty_line, int count);
// ----------------------------------------------------------------



// rendering/   ---------------------------------------------------
int render_header(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *header, _Bool *active);
int form_header(wifi_data *ptr_wifi_data, coord_win *coord, char fields[][256]);

int render_list(wifi_data *ptr_wifi_data, coord_win *coord, WINDOW *list, _Bool *active, char list_wifi[][64], _Bool tab);
// ----------------------------------------------------------------



// wifi_dev/    ---------------------------------------------------
int dns_info(wifi_data *ptr_wifi_data);

int take_list_wifi(wifi_data *ptr_wifi_data, coord_win *coord, char list_wifi[][64]);

int wifi_dev(wifi_data *ptr_wifi_data);
int wifi_info(wifi_data *ptr_wifi_data);
// ----------------------------------------------------------------

#endif



