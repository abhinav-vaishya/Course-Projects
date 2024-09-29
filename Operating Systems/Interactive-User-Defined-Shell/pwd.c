#include "main.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

void pwd() {
    char curr[205];
    getcwd(curr, 205);
    printf("%s", curr);
    printf("\n");
}

void change_path(char curr[]) {
    int i = 0;
    bool ok = false;
    int length = strlen(curr);
    while (1) {
        if (home_dir[i] == '\0') {
            break;
        }
        if (home_dir[i] == curr[i]) {
            i++;
            continue;
        }
        ok = true;
        break;
    }
    if (!ok) {
        char result[length + 5 - i];
        result[0] = '~';
        int j = 1;
        while (i < length) {
            result[j] = curr[i];
            i++;
            j++;
        }
        strcpy(curr, result);
    }
}
