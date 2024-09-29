#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

void cd(char **argv) {
    if (chdir(argv[1])) {
        perror("shell");
    }
}