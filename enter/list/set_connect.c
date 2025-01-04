#include "../../header.h"

int set_connect(wifi_data *ptr_wifi_data, char *wifi_name, char *wifi_pass)
{
    const char *path_supplicant = "/etc/wpa_supplicant/";
    char *wifi_interface = ptr_wifi_data->wifi_interface;

    size_t size_conf = strlen(wifi_name) * 2 + strlen(wifi_pass) + strlen(path_supplicant) + 20;
    char *create_conf_file = malloc(size_conf);

    snprintf(create_conf_file, size_conf, "wpa_passphrase %s %s > %s%s", wifi_name, wifi_pass, path_supplicant, wifi_name);
    system(create_conf_file);
    free(create_conf_file);

    // wpa_supplicant -B -D wext -i wlp8s0 -c kievstar_wpa
    size_t size_connect = strlen(wifi_interface) + strlen(path_supplicant) + strlen(wifi_name) + 37;
    char *connect_to_wifi = malloc(size_connect);

    snprintf(connect_to_wifi, size_connect, "wpa_supplicant -B -D nl80211 -i %s -c %s%s", wifi_interface, path_supplicant, wifi_name);
    system(connect_to_wifi);
    free(connect_to_wifi);



    return 0;
}