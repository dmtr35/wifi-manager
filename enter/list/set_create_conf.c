#include "../../header.h"

int set_create_conf(wifi_data *ptr_wifi_data, char *wifi_name, char *wifi_pass)
{
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    char *wifi_name_cut = wifi_name + 1;

    size_t size_conf = strlen(wifi_name_cut) * 2 + strlen(wifi_pass) + strlen(path_supplicant) + 24;
    char *create_conf_file = malloc(size_conf);


    snprintf(create_conf_file, size_conf, "wpa_passphrase '%s' %s > '%s%s'", wifi_name_cut, wifi_pass, path_supplicant, wifi_name_cut);
    system(create_conf_file);
    free(create_conf_file);

    return 0;
}