#include "main.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"

void sig_handler(int signal) {
    pid_t pid;
    pid = wait(NULL);
    if (0 <= pid) {
        printf("[%d] completed.\n", pid);
    }
    num_of_bg--;
}

bool start(char **argv, int bg) {
    int pid;
    int wait_pid;
    int stat;
    signal(SIGCHLD, sig_handler);
    pid = fork();
    if (0 > pid) {
        perror("shell");
    } else if (!pid) {
        if (0 > execvp(argv[0], argv)) {
            perror("shell");
        }
        exit(1);
    }
    if (bg) {
        addjob(pid, argv[0]);
        printf("[%d] %d\n", num_of_bg++, pid);
        waitpid(pid, &stat, WNOHANG);
    }
    return true;
}
