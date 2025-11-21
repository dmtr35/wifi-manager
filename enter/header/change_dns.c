#include "../../header.h"


int change_dns(char *buffer_dns) {
    char dns_str[27] = {0};
    snprintf(dns_str, sizeof(dns_str), "nameserver %s", buffer_dns);

    size_t size_comm = strlen(dns_str) + 27;

    char *command = calloc(size_comm, sizeof(char));
    snprintf(command, size_comm, "echo '%s' > /etc/resolv.conf", dns_str);

    system(command);
    free(command);

    return 0;
}