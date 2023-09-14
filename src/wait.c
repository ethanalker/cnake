#include <time.h>
#include <stdint.h>

#include "wait.h"
#include "utils.h"

#define WAIT_MAX 100 * 1000 * 1000
#define WAIT_MIN 15 * 1000 * 1000
#define WAIT_RATE 20

uint64_t wait_ns = WAIT_MAX;
struct timespec now;
struct timespec wait_until;

uint64_t as_nsec(struct timespec *ts) {
    return ts->tv_sec * (uint64_t)1000000000L + ts->tv_nsec;
}

struct timespec from_nsec(uint64_t ns) {
    struct timespec ts;
    ts.tv_sec = ns / (uint64_t)1000000000L;
    ts.tv_nsec = ns % (uint64_t)1000000000L;
    return ts;
}

void set_wait_until(void)
{
    if (clock_gettime(CLOCK_MONOTONIC, &now)) die ("clock_gettime");
    wait_until = from_nsec(as_nsec(&now) + wait_ns);
}

void wait(void)
{
    if (clock_gettime(CLOCK_MONOTONIC, &now)) die("clock_gettime");
    uint64_t now_ns = as_nsec(&now);
    uint64_t until_ns = as_nsec(&wait_until);
    if (now_ns < until_ns) {
        struct timespec wait_time = from_nsec(until_ns - now_ns);
        if (nanosleep(&wait_time, &wait_time)) die("nanosleep");
    }
}

void dec_wait_ns(void)
{
    wait_ns -= (wait_ns - WAIT_MIN) / (WAIT_RATE);
}
