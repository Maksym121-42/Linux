#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *f;
    int num;

    f = fopen("dice.txt", "w");

    if (f == NULL) {
        printf("Помилка відкриття файлу\n");
        return 1;
    }

    srand(time(NULL));

    while (1) {
        num = rand() % 6 + 1;

        if (fprintf(f, "%d\n", num) < 0) {
            printf("Досягнуто ліміт розміру файлу!\n");
            break;
        }
    }

    fclose(f);
    return 0;
}
