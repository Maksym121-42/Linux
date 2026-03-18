#include <stdio.h>
#include <stdlib.h>

int global = 5;
int bss;

int main() {
    int local;
    int *heap = malloc(10);

    printf("Text (main): %p\n", main);
    printf("Data (global): %p\n", &global);
    printf("BSS: %p\n", &bss);
    printf("Heap: %p\n", heap);
    printf("Stack: %p\n", &local);

    free(heap);
    return 0;
}
