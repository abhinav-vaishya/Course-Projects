#include "main.h"
#include "stdio.h"
#include "string.h"

void echo(char **argv) {
    if (argv[1][0] == 34) {
        int i = 1;
        int len = strlen(argv[i]);
        while (1) {
            printf("%s", argv[i]);
            if (argv[i][len - 1] == 34) {
                break;
            }
            i++;
        }
        printf("\n");
    } else {
        printf("%s", argv[1]);
        printf("\n");
    }
}