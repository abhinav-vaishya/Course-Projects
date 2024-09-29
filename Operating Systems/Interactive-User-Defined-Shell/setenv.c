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

void set_env(char **args) {
    if (getenv(args[1]) == NULL) {
        setenv(args[1], "", 1);
    }
    if (args[2][0]) {
        setenv(args[1], args[2], 1);
        printf("Environment varialble succesfully set\n");
    } else {
        setenv(args[1], "", 1);
    }
}