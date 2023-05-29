#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

void die(const char *s) {
    perror(s);
    exit(1);
}

void msleep(unsigned int ms)
{
    struct timespec ts;

    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;

    nanosleep(&ts, &ts);
}

