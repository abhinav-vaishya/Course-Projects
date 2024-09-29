#include "main.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define DELIMITER " \t\r\n\a"

int x, y;

void ctrlz(int sig_no) {
    if (sig_no == SIGTSTP) {
        if (fork()) {
            x = 0;
            y = 0;
        } else {
            y = 0;
            signal(SIGTSTP, &ctrlz);
        }
    }
}

void ctrlc(int sig_no) {
    if (fork()) {
        x = 0;
        y = 0;
    } else {
        y = 0;
        signal(SIGINT, &ctrlc);
    }
}

void infinite_loop() {
    signal(SIGINT, ctrlc);
    signal(SIGTSTP, ctrlz);
    char *getline;
    char **args;
    char **argv;
    bool ok;
    bool background;
    int i, j;
    while (ok && !x && !y) {
        strcpy(user, getlogin());
        gethostname(host, 205);
        getcwd(curr, 105);
        if (!i) {
            strcpy(home_dir, curr);
            num_of_bg = 0;
        }
        if (strcmp(home_dir, curr)) {
            strcpy(location, curr);
            change_path(location);
        } else {
            strcpy(location, "~");
        }
        printf("<%s@%s:%s>: ", user, host, location);
        i = 0;
        getline = Read();
        args = arg(getline, ";");
        while (args[i] != NULL) {
            argv = arg(args[i], DELIMITER);
            j = 0;
            if (argv[0] == NULL) {
                i++;
                continue;
            }
            while (1) {
                if (argv[j] == NULL) {
                    j--;
                    break;
                }
                j++;
            }
            background = false;
            int len = strlen(argv[j]);
            if (argv[j][len - 1] == '&') {
                argv[j][len - 1] = ' ';
                background = true;
            }
            ok = run(argv, background);
            free(argv);
            i++;
        }
        free(getline);
    }
}