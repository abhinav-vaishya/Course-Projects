#include "fcntl.h"
#include "limits.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"

#define DELIMITER " \t\r\n\a"

void pinfo(char **argv) {
    char pid[15];
    if (argv[1] != NULL) {
        strcpy(pid, argv[1]);
    } else {
        sprintf(pid, "%d", getpid());
    }
    char procstatfile[] = "/proc/";
    char info[5005];
    strcat(procstatfile, pid);
    char sym[205];
    char exec[205];
    strcpy(sym, procstatfile);
    strcat(procstatfile, "/stat");
    int fd = open(procstatfile, O_RDONLY);
    strcat(sym, "/exe");
    int temp = readlink(sym, exec, sizeof(exec));
    exec[temp] = '\0';
    change_path(exec);
    if (fd == -1) {
        perror("shell");
    } else {
        read(fd, info, 305);
        char **status = arg(info, DELIMITER);
        printf("pid - %s\n", status[0]);
        printf("state - %s\n", status[2]);
        printf("vmsize - %s\n", status[23]);
        printf("executable path - %s\n", exec);
    }
}