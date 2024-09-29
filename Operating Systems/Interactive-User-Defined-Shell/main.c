#include "main.h"
#include "errno.h"
#include "fcntl.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"

int main(int argc, char *argv[]) {
    infinite_loop();
    return 0;
}
