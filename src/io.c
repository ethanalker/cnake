#include <stdlib.h> // malloc
#include <unistd.h> // write
#include <ctype.h> // isdigit
#include <errno.h> // errno
#include <string.h> // strchr

#include "io.h"
#include "term.h"
#include "utils.h"

// input buffer read/write pointers
char *inbuf_start;
char *inbuf_end;
char *pw;
char *pr;

void inbuf_init(void)
{
    inbuf_start = malloc(INBUF_SIZE * sizeof(char));
    inbuf_end = inbuf_start + INBUF_SIZE;
    pw = inbuf_start;
    pr = inbuf_start;
}

char *inbuf_next(char *p)
{
    return ++p < inbuf_end ? p : inbuf_start;
}

void inbuf_write(char c)
{
    char *next = inbuf_next(pw);
    if (next != pr && c != '\0') {
        *pw = c;
        pw = next;
    }
}

char inbuf_read(void)
{
    char c = *pr;
    if (pr != pw) {
        *pr = '\0';
        pr = inbuf_next(pr);
        return c;
    } else {
        return '\0';
    }
}

char read_key(void)
{
    char c = '\0';
    if ((read(0, &c, 1) == -1) && errno != EAGAIN) die("read");

    if (c == '\x1b') {
        char seq[3];
        
        if ((read(0, &seq[0], 1) != 1)) return c;
        if ((read(0, &seq[1], 1) != 1)) return c;
        
        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return 'k';
                case 'B': return 'j';
                case 'C': return 'l';
                case 'D': return 'h';
            }
        }
    } 

    if (c >= 'A' && c <= 'Z')
        c |= 0x20; 

    return c;
}

void dump_to_inbuf(void)
{
    char c;
    while ((c = read_key())) {
        if (strchr(ALLOWED_KEYS, c)) inbuf_write(c);
    }
}

char get_input(void)
{
    dump_to_inbuf();
    return inbuf_read();
}

// returns (0, 0) if check failed
t_coord query_pos(void)
{
    char buf[32] = { '\0' };
    char *pbuf = buf;
    char ystr[6] = { '\0' };
    char *py = ystr;
    char xstr[6] = { '\0' };
    char *px = xstr;

    t_coord pos = { .x = 0, .y = 0 };

    dump_to_inbuf();

    set_blocking();

    write(1, "\x1b[6n", 4);
    read(0, buf, 32);

    set_polling();

    if (*pbuf++ != '\x1b') return pos;
    if (*pbuf++ != '[') return pos;
    while (isdigit(*pbuf)) *py++ = *pbuf++;
    if (*pbuf++ != ';') return pos;
    while (isdigit(*pbuf)) *px++ = *pbuf++;
    if (*pbuf++ != 'R') return pos;

    pos.x = atoi(xstr);
    pos.y = atoi(ystr);
    return pos;
}
