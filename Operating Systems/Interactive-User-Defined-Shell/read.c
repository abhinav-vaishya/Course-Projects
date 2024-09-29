#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

char *Read() {
    char *getinput;
    ssize_t length = 0;
    getinput = NULL;
    getline(&getinput, &length, stdin);
    // int len = strlen(getinput);
    // getinput[len - 1] = '\0';
    return getinput;
}