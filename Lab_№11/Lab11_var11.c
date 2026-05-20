#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct {
    const char *name;
    int sig1;
    int sig2;
    int to_handle;
} ThreadData;

void *signal_worker(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    sigset_t set;
    siginfo_t info;
    int handled = 0;

    sigemptyset(&set);
    sigaddset(&set, data->sig1);
    sigaddset(&set, data->sig2);

    while (handled < data->to_handle) {
        int sig = sigwaitinfo(&set, &info);
        if (sig == -1) {
            perror("sigwaitinfo");
            continue;
        }

        printf("[%s] Отримано сигнал %d від PID %d\n",
               data->name, sig, info.si_pid);
        handled++;
    }

    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    sigset_t blocked;
    ThreadData d1 = {"Thread-1", SIGUSR1, SIGINT, 2};
    ThreadData d2 = {"Thread-2", SIGUSR2, SIGTERM, 2};

    sigemptyset(&blocked);
    sigaddset(&blocked, SIGUSR1);
    sigaddset(&blocked, SIGINT);
    sigaddset(&blocked, SIGUSR2);
    sigaddset(&blocked, SIGTERM);

    if (pthread_sigmask(SIG_BLOCK, &blocked, NULL) != 0) {
        perror("pthread_sigmask");
        return 1;
    }

    if (pthread_create(&t1, NULL, signal_worker, &d1) != 0) {
        perror("pthread_create t1");
        return 1;
    }

    if (pthread_create(&t2, NULL, signal_worker, &d2) != 0) {
        perror("pthread_create t2");
        return 1;
    }

    sleep(1);

    kill(getpid(), SIGUSR1);
    kill(getpid(), SIGUSR2);
    kill(getpid(), SIGINT);
    kill(getpid(), SIGTERM);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
