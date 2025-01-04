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

