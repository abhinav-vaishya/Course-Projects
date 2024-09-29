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

void overkill() {
    int cnt = 1;
    bool ok = 0;
    size_t sz = 0;
    char *str = NULL, *str1;
    char command_name[205] = {}, *temp[205] = {NULL}, pid_string[205] = {};
    FILE *fd = fopen("jobs.txt", "r");
    ssize_t readsize;
    while ((readsize = getline(&str, &sz, fd)) > -1) {
        char path[256] = "/proc/\0";
        if (!(cnt & 1)) {
            ok = 1;
            int cnt1 = 0;
            str1 = str;
            while (str1[cnt1] != '[') {
                command_name[cnt1] = str1[cnt1++];
            }
            temp[0] = command_name;
            int j = 0;
            cnt1++;
            while (str1[cnt1] != ']') {
                pid_string[j++] = str1[cnt1++];
            }
            int pid = atoi(pid_string);
            strcat(path, pid_string);
            strcat(path, "/status");
            if (fopen(path, "r")) kill(pid, 9);
        }
        cnt++;
    }
    fclose(fd);
}