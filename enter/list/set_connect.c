#include "../../header.h"

int set_connect(wifi_data *ptr_wifi_data, char *wifi_name, char *wifi_pass)
{
    char *wifi_interface = ptr_wifi_data->wifi_interface;

    size_t size_connect = strlen(wifi_interface) + strlen(path_supplicant) + strlen(wifi_name) + 37;
    char *connect_to_wifi = malloc(size_connect);

    snprintf(connect_to_wifi, size_connect, "wpa_supplicant -B -D nl80211 -i %s -c %s%s", wifi_interface, path_supplicant, wifi_name);
    system(connect_to_wifi);
    free(connect_to_wifi);

    return 0;
    
}