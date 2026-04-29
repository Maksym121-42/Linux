#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(void) {
    int n = 4;
    unsigned long long work = 600000000ULL;

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            if (i >= 2) {
                nice(10);
            }

            clock_t start = clock();

            volatile unsigned long long x = 0;
            for (unsigned long long k = 0; k < work; k++) {
                x += k % 3;
            }

            clock_t end = clock();
            double t = (double)(end - start) / CLOCKS_PER_SEC;

            printf("pid=%d nice=%d time=%.3f s\n", getpid(), getpriority(0, 0), t);
            _exit(0);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
