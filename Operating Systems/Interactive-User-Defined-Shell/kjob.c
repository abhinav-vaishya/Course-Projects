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

void kjob(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Use a proper format: kjob job-number signal-number\n");
        return;
    } else {
        int job_no = atoi(args[1]), sig_no = atoi(args[2]);
        int cnt = 1, cnt1;
        size_t sz = 0;
        bool ok = false;
        char *str = NULL, *str1;
        char command_name[205] = {}, *temp[205] = {NULL}, pid_string[205] = {};
        FILE *fd = fopen("jobs.txt", "r");
        ssize_t readsize;
        while ((readsize = getline(&str, &sz, fd)) > -1) {
            if (job_no * 2 == cnt) {
                cnt1 = 0;
                str1 = str;
                ok = true;
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
                kill(pid, sig_no);
                break;
            }
            cnt++;
        }
        fclose(fd);
    }
}