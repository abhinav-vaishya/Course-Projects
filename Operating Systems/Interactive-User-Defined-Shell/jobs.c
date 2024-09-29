#include "dirent.h"
#include "errno.h"
#include "fcntl.h"
#include "main.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"

void itoa(char str[], int num) {
    int l = 0;
    int temp = num;
    while (temp) {
        l++;
        temp /= 10;
    }
    int i = 0;
    while (i < l) {
        int d = num % 10;
        str[l - (i + 1)] = d + '0';
        num = num / 10;
        i++;
    }
    str[l] = '\0';
}

void addjob(int pid, char *command_name) {
    char exec[1005];
    memset(exec, '\0', 1005);
    char process_id[1005];
    memset(process_id, '\0', 1005);
    char directory[1005];
    memset(directory, '\0', 1005);
    char line[1005];
    memset(line, '\0', 1005);
    char executable_path[1005];
    memset(executable_path, '\0', 1005);
    FILE *fd2 = fopen("jobs.txt", "a");
    int i = 0;
    for (i = 0; i < 5; i++) {
        if (!i)
            directory[i] = '/';
        else if (i == 1)
            directory[i] = 'p';
        else if (i == 2)
            directory[i] = 'r';
        else if (i == 3)
            directory[i] = 'o';
        else if (i == 4)
            directory[i] = 'c';
        else if (i == 5)
            directory[i] = '/';
    }
    FILE *fd1 = fopen(directory, "r");
    char snum[55];
    itoa(snum, pid);
    strcat(directory, snum);
    strcpy(executable_path, directory);
    strcat(executable_path, "/exe");
    if (fd1 && fd2) {
        fprintf(fd2, "%s\n", directory);
        fclose(fd1);
        fprintf(fd2, "%s[%d]\n", command_name, pid);
        fclose(fd2);
    } else {
        fclose(fd1);
        fclose(fd2);
    }
}

void jobs() {
    char *str = NULL;
    size_t sz = 0;
    int cnt = 0;
    ssize_t readsize;
    FILE *fd = fopen("jobs.txt", "r");
    while ((readsize = getline(&str, &sz, fd)) > -1) {
        if (cnt & 1) {
            printf("%s", str);
        } else {
            printf("[%d] ", 1 + (cnt / 2));
            DIR *dir = opendir(str);
            if (!dir) {
                printf("Stopped ");
            } else {
                printf("Running ");
            }
            closedir(dir);
        }
        cnt++;
    }
    if (str) free(str);
    fclose(fd);
};