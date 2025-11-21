#include "../header.h"


int dns_info(wifi_data *ptr_wifi_data)
{
    char *dns = ptr_wifi_data->dns;
    memset(dns, '\0', strlen(dns));

    FILE *fp = fopen("/etc/resolv.conf", "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        // проверяем начинается ли строка на "nameserver"
        if (strncmp(line, "nameserver", 10) == 0) {
            // считываем dns после ключевого слова
            sscanf(line, "nameserver %255s", dns);
            break;
        }
    }

    fclose(fp);
    return 0;
}