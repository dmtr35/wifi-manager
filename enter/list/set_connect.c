#include "../../header.h"

int set_connect(wifi_data *ptr_wifi_data, char *wifi_name, char *wifi_pass)
{
    char *wifi_interface = ptr_wifi_data->wifi_interface;

    size_t size_connect = strlen(wifi_interface) + strlen(path_supplicant) + strlen(wifi_name) + 78;
    size_t size_dhclient = strlen(wifi_interface) + 26;
    char *command = malloc(size_connect);

    snprintf(command, size_connect, "wpa_supplicant -B -D nl80211 -i %s -c '%s%s' -O /run/wpa_supplicant >/dev/null 2>&1", wifi_interface, path_supplicant, wifi_name);
    system(command);
    sleep(1);

    snprintf(command, size_dhclient, "dhclient %s >/dev/null 2>&1", wifi_interface);
    system(command);
    sleep(1);
    wifi_info(ptr_wifi_data);

    free(command);
    return 0;
    
}