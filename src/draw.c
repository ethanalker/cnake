#include <string.h> // strcat, strlen, etc
#include <stdio.h> // sprintf
#include <unistd.h> // write

#include "draw.h"

char wbuf[WBUF_SIZE];
char *pbuf = wbuf;

void reset_buf(void)
{
    *wbuf = '\0';
    pbuf = wbuf;
}

void write_str(const char *s)
{
    strcat(pbuf, s);
    pbuf += strlen(s);
}

void write_chr(const char c)
{
    strncat(pbuf, &c, 1);
    pbuf++;
}

void write_int(const int x)
{
    sprintf(pbuf, "%d", x);
    pbuf += strlen(pbuf);
}

void draw_char(const unsigned int x, const unsigned int y, const char c)
{
    write_str("\x1b[");
    write_int(y);
    write_chr(';');
    write_int(x);
    write_chr('H');
    write_chr(c);
}

void draw_screen(void)
{
    write(1, wbuf, strlen(wbuf));
    reset_buf();
}
