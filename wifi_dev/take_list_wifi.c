#include "../header.h"



int take_list_wifi(wifi_data *ptr_wifi_data, coord_win *coord, char list_wifi[][INT_64])
{
    struct timespec start, end;
    double elapsed;
    int i = 0, k = 0;

    char *wifi_interface = ptr_wifi_data->wifi_interface;
    int *full_lines = &coord->full_lines;
    size_t size_command = strlen(wifi_interface) + 67;
    FILE *fp;
    char buffer[SIZE_BUFF] = {0};
    char list_config[10][INT_64] = {0};
    char wifi_list_buff[30][INT_64] = {0};

    check_config_file(list_config);
    // size_t tt2 = sizeof(list_config);
    
    *full_lines = 0;
    char *command = malloc(size_command);
    snprintf(command, size_command, "sudo iw dev %s scan 2>/dev/null | grep 'SSID:' | sed 's/^.*SSID: //'", wifi_interface);
    
    fp = popen(command, "r");
    if (fp == NULL) {
        // perror("Error executing iw command");
        free(command);
        return -1;
    }

    while (i < NUM_WIFI_LIST) {
        if (fgets(buffer, SIZE_BUFF, fp) == NULL) {
            break;
        }
        if (buffer[0] == '\n') {
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        size_t size_buf = strlen(buffer);

        for (int j = 0; j < 10; ++j) {
            if (strcmp(buffer, list_config[j]) == 0) {
                snprintf(list_wifi[i++], size_buf + 2, "*%s", buffer);
                goto exit;
            }
        }
        snprintf(wifi_list_buff[k++], size_buf + 2, " %s", buffer);

        exit:
        (*full_lines)++;
    }

    for (int t = 0; i < NUM_WIFI_LIST; ++i, ++t) {
        if (wifi_list_buff[t][0] == '\0') {
            break;
        }
        strcpy(list_wifi[i], wifi_list_buff[t]);
    }

    free(command);
    pclose(fp);
}