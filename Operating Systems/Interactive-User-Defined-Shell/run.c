#include "main.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

bool run(char **argv, int background) {
    bool pip = false;
    bool redi = false;
    for (int i = 0; argv[i] != NULL; i++) {
        if (!strcmp(argv[i], "|")) {
            pip = true;
            piping(argv);
            return true;
        }
    }
    for (int i = 0; argv[i] != NULL && !pip; i++) {
        if ((strcmp(argv[i], ">")) == 0 || (strcmp(argv[i], "<")) == 0 ||
            (strcmp(argv[i], ">>")) == 0) {
            redi = true;
            break;
        }
    }
    if (redi) {
        redirection(argv);
        return true;
    }
    if (argv[0] == NULL) {
        return true;
    }
    if (!strcmp(argv[0], "quit")) {
        exit(0);
    } else if (!strcmp(argv[0], "kjob")) {
        kjob(argv);
        return true;
    } else if (!strcmp(argv[0], "setenv")) {
        set_env(argv);
        return true;
    } else if (!strcmp(argv[0], "unsetenv")) {
        unset_env(argv);
        return true;
    } else if (!strcmp(argv[0], "jobs")) {
        jobs();
        return true;
    } else if (!strcmp(argv[0], "overkill")) {
        overkill();
        return true;
    } else if (!strcmp(argv[0], "fg")) {
        fg(argv[1]);
        return true;
    } else if (!strcmp(argv[0], "bg")) {
        bg(argv[1]);
        return true;
    } else if (!strcmp(argv[0], "echo")) {
        echo(argv);
        return true;
    } else if (!strcmp(argv[0], "pwd")) {
        pwd();
        return true;
    } else if (!strcmp(argv[0], "cd")) {
        cd(argv);
        return true;
    } else if (!strcmp(argv[0], "ls")) {
        ls(argv);
        return true;
    } else if (!strcmp(argv[0], "pinfo")) {
        pinfo(argv);
        return true;
    } else {
        return start(argv, background);
    }
    return true;
}