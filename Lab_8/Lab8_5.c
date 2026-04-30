#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int id;
} Obj;

int cmp_obj(const void *a, const void *b) {
    const Obj *x = (const Obj *)a;
    const Obj *y = (const Obj *)b;
    if (x->key < y->key) return -1;
    if (x->key > y->key) return 1;
    return 0;
}

void swap_obj(Obj *a, Obj *b) {
    Obj t = *a;
    *a = *b;
    *b = t;
}

void my_qsort_rec(Obj *a, int l, int r) {
    int i = l;
    int j = r;
    Obj pivot = a[(l + r) / 2];

    while (i <= j) {
        while (cmp_obj(&a[i], &pivot) < 0) i++;
        while (cmp_obj(&a[j], &pivot) > 0) j--;
        if (i <= j) {
            swap_obj(&a[i], &a[j]);
            i++;
            j--;
        }
    }

    if (l < j) my_qsort_rec(a, l, j);
    if (i < r) my_qsort_rec(a, i, r);
}

void my_qsort(Obj *a, int n) {
    if (n > 1) my_qsort_rec(a, 0, n - 1);
}

void print_arr(const char *name, Obj *a, int n) {
    printf("%s:\n", name);
    for (int i = 0; i < n; i++) {
        printf("(%d,%d) ", a[i].key, a[i].id);
    }
    printf("\n");
}

int count_unstable_pairs(Obj *a, int n) {
    int c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i].key == a[j].key && a[i].id > a[j].id) c++;
        }
    }
    return c;
}

int main(void) {
    Obj src[] = {
        {3,0}, {1,1}, {3,2}, {2,3}, {1,4}, {2,5},
        {3,6}, {1,7}, {2,8}, {3,9}, {1,10}, {2,11}
    };
    int n = sizeof(src) / sizeof(src[0]);

    Obj sys[12];
    Obj own[12];

    memcpy(sys, src, sizeof(src));
    memcpy(own, src, sizeof(src));

    qsort(sys, n, sizeof(Obj), cmp_obj);
    my_qsort(own, n);

    print_arr("Початковий масив", src, n);
    print_arr("Системний qsort", sys, n);
    print_arr("Власний qsort", own, n);

    printf("Порушення порядку рівних ключів (системний): %d\n", count_unstable_pairs(sys, n));
    printf("Порушення порядку рівних ключів (власний): %d\n", count_unstable_pairs(own, n));

    return 0;
}
