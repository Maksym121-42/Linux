#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp");
        return 1;
    }

    wait(NULL);
    return 0;
}
