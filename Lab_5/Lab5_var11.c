#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    size_t n = 6;
    uint64_t *a = malloc(n * sizeof(a));
    if (a == NULL) return 1;

    for (size_t i = 0; i < n; i++) {
        a[i] = 1000 + i;
    }

    printf("%llu\n", (unsigned long long)a[n - 1]);
    free(a);
    return 0;
}
