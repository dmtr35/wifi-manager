#include "../header.h"


int take_list_wifi(wifi_data *ptr_wifi_data, char **list_wifi)
{
    char *wifi_interface = ptr_wifi_data->wifi_interface;
    size_t size_command = strlen(wifi_interface) + 55;
    FILE *fp;
    char buffer[SIZE_BUFF];
    int count = 0;

    char *command = malloc(size_command);
    snprintf(command, size_command, "sudo iw dev %s scan | grep 'SSID:' | sed 's/^.*SSID: //'", wifi_interface);

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error executing iw command");
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
        printf("%s\n", buffer);
        strcpy(list_wifi[i], buffer);
        count++;
    }

    pclose(fp);
}