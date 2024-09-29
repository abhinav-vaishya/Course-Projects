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

void unset_env(char **args) {
    if (getenv(args[1]) == NULL) {
        printf("Environment variable does not exist.\n");
    } else if (unsetenv(args[1]) != 0) {
        printf("Error.\n");
    }
}