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

void bg(char *job_num) {
    int job_no = atoi(job_num);
    int cnt = 1;
    size_t sz = 0;
    bool ok = true;
    char *str = NULL, *str1;
    char command_name[100] = {}, *temp[100] = {NULL}, pid_string[100] = {};
    FILE *fd = fopen("jobs.txt", "r");
    ssize_t readsize;
    while ((readsize = getline(&str, &sz, fd)) > -1) {
        if (job_no * 2 == cnt) {
            int cnt1 = 0;
            ok = true;
            str1 = str;
            while (str1[cnt1] != '[') {
                command_name[cnt1] = str1[cnt1++];
            }
            temp[0] = command_name;
            cnt1++;
            int j = 0;
            while (str1[cnt1] != ']') {
                pid_string[j++] = str1[cnt1++];
            }
            int pid = atoi(pid_string);
            kill(pid, SIGKILL);
            pid_t abc;
            abc = fork();
            if (!abc) {
                addjob(getpid(), temp[0]);
                int err = execvp(temp[0], temp);
                if (err < 0) {
                    printf("Invalid command.\n");
                    kill(getpid(), 9);
                }
            }
            break;
        }
        cnt++;
    }
    if (!ok) printf("Invalid job number.\n");
};
