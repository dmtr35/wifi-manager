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


