#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

void die(const char *s) {
    perror(s);
    exit(1);
}
