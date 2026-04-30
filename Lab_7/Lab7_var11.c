#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CMDS 4096
#define MAX_NAME 128
#define MAX_LINE 4096

typedef struct {
    char name[MAX_NAME];
    int count;
} CmdStat;

int extract_cmd(char *line, char out[MAX_NAME]) {
    char *p = line;
    int i = 0;

    while (*p && isspace((unsigned char)*p)) p++;
    while (*p && isdigit((unsigned char)*p)) p++;
    while (*p && isspace((unsigned char)*p)) p++;

    if (*p == '\0' || *p == '\n') return 0;

    while (*p && !isspace((unsigned char)*p) && *p != '|' && *p != ';' && *p != '&') {
        if (i < MAX_NAME - 1) out[i++] = *p;
        p++;
    }
    out[i] = '\0';
    if (i == 0) return 0;

    if (strcmp(out, "sudo") == 0) {
        while (*p && isspace((unsigned char)*p)) p++;
        i = 0;
        while (*p && !isspace((unsigned char)*p) && *p != '|' && *p != ';' && *p != '&') {
            if (i < MAX_NAME - 1) out[i++] = *p;
            p++;
        }
        out[i] = '\0';
        if (i == 0) return 0;
    }

    return 1;
}

int cmp_stat(const void *a, const void *b) {
    const CmdStat *x = (const CmdStat *)a;
    const CmdStat *y = (const CmdStat *)b;
    if (x->count != y->count) return x->count - y->count;
    return strcmp(x->name, y->name);
}

int main(void) {
    CmdStat stats[MAX_CMDS];
    int n = 0;

    FILE *fp = popen("bash -c \"set -o history; HISTFILE=$HOME/.bash_history; history -r; history\"", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        char cmd[MAX_NAME];
        if (!extract_cmd(line, cmd)) continue;

        int found = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(stats[i].name, cmd) == 0) {
                stats[i].count++;
                found = 1;
                break;
            }
        }

        if (!found && n < MAX_CMDS) {
            strncpy(stats[n].name, cmd, MAX_NAME - 1);
            stats[n].name[MAX_NAME - 1] = '\0';
            stats[n].count = 1;
            n++;
        }
    }

    pclose(fp);

    if (n == 0) {
        printf("Історія команд порожня або недоступна.\n");
        return 0;
    }

    qsort(stats, n, sizeof(CmdStat), cmp_stat);

    int min_count = stats[0].count;
    printf("Найменш використовувані команди (кількість викликів = %d):\n", min_count);
    for (int i = 0; i < n; i++) {
        if (stats[i].count == min_count) {
            printf("%s\n", stats[i].name);
        }
    }

    return 0;
}

