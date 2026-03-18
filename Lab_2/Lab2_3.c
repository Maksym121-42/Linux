#include <stdio.h>
#include <stdlib.h>

int a = 5;      // data
int b;          // bss

void test() {
    int big1[1000];
    int big2[1000];
    int y;

    printf("Stack in test(): %p\n", &y);
}



int main() {
    int x;      // stack
    int *p = malloc(sizeof(int)); // heap

    printf("Text (main): %p\n", main);
    printf("Data (a): %p\n", &a);
    printf("BSS (b): %p\n", &b);
    printf("Heap: %p\n", p);
    printf("Stack (x): %p\n", &x);

    test();
    free(p);
    return 0;
}
