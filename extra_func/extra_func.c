#include "../header.h"
// 255.255.255.0
// преобразование маски подсети в вид cidr (/24)
int netmask_to_cidr(const char *netmask)
{
    char netmask_copy[16];
    strncpy(netmask_copy, netmask, sizeof(netmask_copy) - 1);
    netmask_copy[sizeof(netmask_copy) - 1] = '\0'; // Безопасный конец строки

    uint32_t mask;
    int cidr = 0;

    char *ptr = strtok(netmask_copy, ".");
    while (ptr != NULL) {
        mask = atoi(ptr);

        // Подсчёт установленных битов в байте
        while (mask) {
            cidr += mask & 1;
            mask >>= 1;
        }

        ptr = strtok(NULL, ".");
    }

    return cidr;
}

// преобразование cidr в mask
int cidr_to_netmask(char *mask_cidr, char *wifi_mask)
{
    int cidr = atoi(mask_cidr);                                 // Преобразуем CIDR (например, 24) в число
    if (cidr < 0 || cidr > 32) {
        printf("Invalid CIDR value\n");
        return -1;
    }

    unsigned int netmask = 0xFFFFFFFF << (32 - cidr);           // Сдвигаем единичные биты
    snprintf(wifi_mask, 16, "%d.%d.%d.%d", 
             (netmask >> 24) & 0xFF,                            // Старшие 8 бит
             (netmask >> 16) & 0xFF,                            // Следующие 8 бит
             (netmask >> 8) & 0xFF,                             // Еще 8 бит
             netmask & 0xFF);                                   // Младшие 8 бит

    return 0;
}

// высчитываем кооодинаты окон
int calculate_coord_win(wifi_data *ptr_wifi_data, coord_win *coord)
{
    int *height = &coord->height;
    int *width = &coord->width;
    int *height_win = &coord->height_win;
    int *width_win = &coord->width_win;
    int *height_x = &coord->height_x;
    int *width_y = &coord->width_y;

    *height_win = *height / 2;
    if (*height_win < 15) {
        *height_win = 15;
    }

    *width_win = *width / 2;
    if (*width_win < 33) {
        *width_win = 33;
    }

    *height_x = (*height - *height_win) / 2;
    *width_y = (*width - *width_win) / 2;
}

// проверка ip и маски регулярными выражениями
int validate_input(const char *value, const char *pattern)
{
    
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Regular expression compilation error\n");        
        return 0;
    }

    ret = regexec(&regex, value, 0, NULL, 0);
    regfree(&regex);                                            // освобождаем ресурсы

    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regular expression execution error\n");
        return 0;
    }
}

// удалить все процессы связанные с wifi интерфейсом
void del_wifi_proc(char *interface)
{
    size_t size_command = strlen(interface) + 79;
    char *command = malloc(size_command);
    snprintf(command, size_command, "ps -aux | grep %s | awk '{print $2}' | while read LINE; do sudo kill $LINE; done", interface);
    usleep(100000);

    system(command);
    free(command);
}

// выключить интерфейс
void iface_down(char *interface)
{
    size_t size_command = strlen(interface) + 18;
    char *command = malloc(size_command);
    snprintf(command, size_command, "ip link set %s down", interface);
    usleep(100000);

    system(command);
    free(command);
}
// включить интерфейс
void iface_up(char *interface)
{
    size_t size_command = strlen(interface) + 16;
    char *command = malloc(size_command);
    snprintf(command, size_command, "ip link set %s up", interface);
    usleep(100000);

    system(command);
    free(command);
}

// check config file
int check_config_file(char list_config[][INT_64])
{
    int i = 0;
    DIR *dir = opendir(path_supplicant);

    if (dir == NULL){
        perror("Error opening directory");
        return 1;
    }
    struct dirent *entry;                                   // прочитать содержимое директории

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, "action_wpa.sh") == 0 || strcmp(entry->d_name, "functions.sh") == 0 || strcmp(entry->d_name, "ifupdown.sh") == 0) {
            continue;
        }

        strcpy(list_config[i], entry->d_name);
        i++;
    }

    closedir(dir);

    return 0;
}
// достать пароль с конфига
int get_pass(char *wifi_name, char *wifi_pass)
{
    size_t size_path = strlen(path_supplicant) + strlen(wifi_name) + 1;
    char *full_path = malloc(size_path);
    if (!full_path) {
        // perror("Ошибка выделения памяти");
        return 1;
    }

    snprintf(full_path, size_path, "%s%s", path_supplicant, wifi_name);

    FILE *file = fopen(full_path, "r");
    if (!file) {
        free(full_path);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "#psk=")) {
            char *start = strchr(line, '"');
            start++;
            char *end = strrchr(line, '"');
            *end = '\0';
            size_t len = end - start;
            if (len <= INT_64) {
                strcpy(wifi_pass, start);
            }
            break;
        }
    }
    
    free(full_path);
    fclose(file);
}

