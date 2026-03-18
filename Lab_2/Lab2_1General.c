#include <stdio.h>
#include <time.h>

int main() {
    time_t t = 2147483640;

    while (t < 2147483647) {
        t++;
    }

    printf("Останнє значення: %ld\n", (long)t);
    printf("Дата: %s", asctime(gmtime(&t)));
    printf("Розмір time_t: %ld байт\n", sizeof(time_t));

    return 0;
}
