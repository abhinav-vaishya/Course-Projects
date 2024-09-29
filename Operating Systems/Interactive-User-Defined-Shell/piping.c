#include "errno.h"
#include "fcntl.h"
#include "main.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"

void piping(char **arg) {
    int source;
    int destination;
    dup2(0, source);
    dup2(1, destination);
    pid_t pid;
    char *str[205] = {NULL};
    int fd[2][2];
    bool stop = false;
    int left_idx = 0;
    int right_idx = 0;
    int no_of_pipes = 0;
    int temp = 0;
    while (1) {
        if (arg[temp] == NULL) break;
        if ('<' == arg[temp][0])
            left_idx = temp + 1;
        else if ('|' == arg[temp][0])
            no_of_pipes++;
        else if ('>' == arg[temp][0])
            right_idx = temp + 1;
        temp++;
    }
    int i = 0;
    int k = 0;
    temp = 0;
    while (arg[i] && !stop) {
        k = 0;
        while ((arg[i][0] != '|' && arg[i][0] != '<' && arg[i][0] != '>')) {
            str[k] = arg[i];
            i++;
            if (arg[i] == NULL) {
                stop = true;
                break;
            }
            k++;
        }
        if (stop) k++;
        i++;
        int f01 = fd[0][1];
        int fp1 = fd[(no_of_pipes + 1) % 2][0];
        int fj10 = fd[(temp + 1) % 2][0];
        int fj1 = fd[temp % 2][1];
        int fj0 = fd[temp % 2][0];
        pipe(fd[temp % 2]);
        if (!temp) {
            if (left_idx) {
                if (arg[i - 1][0] == '<') {
                    i += 2;
                }
            }
        }
        if (temp - no_of_pipes == 0) {
            if (right_idx) {
                if (arg[i - 1][0] == '>') {
                    i += 2;
                }
            }
        }
        pid = fork();
        if (0 > pid) {
            if (no_of_pipes - temp != 0) {
                close(fd[temp % 2][1]);
            }
            printf("Child process not created\n");
            return;
        }
        if (!pid) {
            if (no_of_pipes - temp == 0) {
                if (right_idx) {
                    int output = open(arg[right_idx],
                                      O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(output, 1);
                    close(output);
                }
                dup2(fd[(no_of_pipes + 1) % 2][0], 0);
            } else if (!temp) {
                if (left_idx) {
                    int input = open(arg[left_idx], O_RDONLY);
                    if (input != -1) {
                        dup2(input, 0);
                        close(input);
                    }
                }
                dup2(fd[0][1], 1);
            } else {
                if ((temp + 1) % 2 == 0)
                    dup2(fd[0][0], 0);
                else
                    dup2(fd[1][0], 0);
                if (temp % 2 == 0)
                    dup2(fd[0][0], 1);
                else
                    dup2(fd[1][0], 1);
            }
            if (0 > execvp(str[0], str)) {
                kill(getpid(), SIGTERM);
            }
        }
        if (!temp) {
            close(fd[0][1]);
        } else if (no_of_pipes - temp == 0) {
            if ((no_of_pipes + 1) % 2 == 0)
                close(fd[0][0]);
            else
                close(fd[1][0]);
        } else {
            if ((temp + 1) % 2 == 0)
                close(fd[0][0]);
            else
                close(fd[1][0]);
            if (temp % 2 == 0)
                close(fd[0][1]);
            else
                close(fd[1][1]);
        }
        waitpid(pid, NULL, 0);
        temp++;
    }
}