#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

void run_shell_id(void) {
    printf("1) id через shell (system):\n");
    system("id");
    printf("\n");
}

void run_exec_id(char *const envp[], const char *title) {
    pid_t pid = fork();

    if (pid == 0) {
        char *argv[] = {"id", NULL};
        execve("/usr/bin/id", argv, envp);
        _exit(1);
    }

    wait(NULL);
    printf("\n");
}

int main(void) {
    printf("Поточний процес: uid=%d euid=%d gid=%d egid=%d\n\n",
           getuid(), geteuid(), getgid(), getegid());

    run_shell_id();

    printf("2) id через прямий системний виклик (execve) з поточним середовищем:\n");
    run_exec_id(environ, "current");

    printf("3) id через execve з порожнім середовищем:\n");
    char *empty_env[] = {NULL};
    run_exec_id(empty_env, "empty");

    return 0;
}
