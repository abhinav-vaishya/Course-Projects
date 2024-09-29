#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

char **arg(char *getline, char *delimiter) {
    char *token;
    char **input = malloc(100 * sizeof(char *));
    token = strtok(getline, delimiter);
    int i;
    for (i = 0; token != NULL; i++) {
        input[i] = token;
        token = strtok(NULL, delimiter);
    }
    input[i] = NULL;
    return input;
}
