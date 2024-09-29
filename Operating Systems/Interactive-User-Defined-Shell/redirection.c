#include "errno.h"
#include "fcntl.h"
#include "main.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"

void redirection(char **args) {
    int fd1;
    int fd2;
    char *input_file;
    char *output_file;
    int pid;
    bool in = false;
    bool out = false;
    bool out1 = false;
    int source = dup(0);
    int destination = dup(1);
    int i = 1;
    while (args[i] != NULL) {
        if (!strcmp(args[i], ">")) {
            args[i] = NULL;
            output_file = args[i + 1];
            args[i + 1] = NULL;
            out = true;
            i++;
        } else if (!strcmp(args[i], "<")) {
            args[i] = NULL;
            input_file = args[i + 1];
            args[i + 1] = NULL;
            in = true;
            i++;
        } else if (!strcmp(args[i], ">>")) {
            args[i] = NULL;
            output_file = args[i + 1];
            args[i + 1] = NULL;
            out1 = true;
            i++;
        }
        i++;
    }
    if (in) {
        fd1 = open(input_file, O_RDONLY);
        dup2(fd1, 0);
        close(fd1);
        if (!(fd1 > 0)) {
            perror("shell");
            exit(errno);
        }
    }
    if (out) {
        fd2 = open(output_file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
        dup2(fd2, 1);
        close(fd2);
        if (!(fd2 > 0)) {
            perror("shell");
            exit(errno);
        }
    }
    if (out1) {
        fd2 = open(output_file, O_APPEND | O_CREAT | O_WRONLY, 0644);
        dup2(fd2, 1);
        close(fd2);
        if (!(fd2 > 0)) {
            perror("shell");
            exit(errno);
        }
    }
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            perror("shell");
        }
        exit(1);
    }
    dup2(source, 0);
    dup2(destination, 1);
    close(source);
    close(destination);
}