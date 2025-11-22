#include "../../header.h"


int change_dns(char *buffer_dns) {
    FILE *f = fopen("/etc/resolv.conf", "w");
    if (!f) return -1;

    // Если пользователь ввёл "0" → очищаем файл
    if (strcmp(buffer_dns, "0") == 0) {
        fclose(f);
        return 0;
    }

    fprintf(f, "nameserver %s\n", buffer_dns);
    fclose(f);
    
    return 0;
}