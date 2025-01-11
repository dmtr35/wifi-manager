#include "../header.h"



int take_list_wifi(wifi_data *ptr_wifi_data, coord_win *coord, char **list_wifi)
{
    struct timespec start, end;
    double elapsed;

    char *wifi_interface = ptr_wifi_data->wifi_interface;
    int *full_lines = &coord->full_lines;
    size_t size_command = strlen(wifi_interface) + 55;
    FILE *fp;
    char buffer[SIZE_BUFF] = {0};
    char list_config[10][INT_64] = {0};
    size_t tt1 = sizeof(list_config);

    check_config_file(list_config);
    size_t tt2 = sizeof(list_config);
    
    *full_lines = 0;
    char *command = malloc(size_command);
    snprintf(command, size_command, "sudo iw dev %s scan | grep 'SSID:' | sed 's/^.*SSID: //'", wifi_interface);
    
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error executing iw command");
        free(command);
        return -1;
    }

    for (int i = 0; i < NUM_WIFI_LIST; ++i) {
        if (fgets(buffer, SIZE_BUFF, fp) == NULL) {
            break;
        }
        if (buffer[0] == '\n') {
            --i;
            continue;
        }
        size_t size_buf = strlen(buffer) - 1;
        buffer[size_buf] = '\0';

        for (int j = 0; j < 10; ++j) {
            if (strcmp(buffer, list_config[j]) == 0) {
                snprintf(list_wifi[i], size_buf + 2, "*%s", buffer);
                goto exit;
            }
        }
        snprintf(list_wifi[i], size_buf + 1, " %s", buffer);

        exit:
        (*full_lines)++;
    }

    free(command);
    pclose(fp);
}