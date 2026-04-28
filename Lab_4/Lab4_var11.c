#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    const size_t chunk = 8 * 1024 * 1024;
    size_t total = 0;
    size_t blocks = 0;

    while (1) {
        void *p = malloc(chunk);

        if (p == NULL) {
            printf("malloc повернув NULL\n");
            printf("errno = %d (%s)\n", errno, strerror(errno));
            printf("Успішно виділено до відмови: %zu байт (%zu МБ)\n", total, total / (1024 * 1024));
            break;
        }

        memset(p, 0, chunk);
        total += chunk;
        blocks++;
        printf("Блок %zu: сумарно %zu МБ\n", blocks, total / (1024 * 1024));
    }

    return 0;
}
