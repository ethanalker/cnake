#include <string.h> // strcat, strlen, etc
#include <stdio.h> // sprintf
#include <unistd.h> // write

#include "draw.h"

char wbuf[WBUF_SIZE];
char *pwbuf = wbuf;

void reset_buf(void)
{
    *wbuf = '\0';
    pwbuf = wbuf;
}

void write_str(char **pbuf, const char *s)
{
    strcat(*pbuf, s);
    (*pbuf) += strlen(s);
}

void write_int(char **pbuf, const int x)
{
    sprintf(*pbuf, "%d", x);
    (*pbuf) += strlen(*pbuf);
}

void move_cursor(char **pbuf, const unsigned int x, const unsigned int y)
{
    write_str(pbuf, "\x1b[");
    write_int(pbuf, y);
    write_str(pbuf, ";");
    write_int(pbuf, x);
    write_str(pbuf, "H");
}

void draw_str(const unsigned int x, const unsigned int y, const char *s, const char *fx)
{
    write_str(&pwbuf, fx);
    move_cursor(&pwbuf, x, y);
    write_str(&pwbuf, s);
}

void refresh_screen(void)
{
    write(1, wbuf, strlen(wbuf));
    reset_buf();
}

void move_now(const unsigned int x, const unsigned int y)
{
    char buf[16] = { '\0' };
    char *pbuf = buf;
    move_cursor(&pbuf, x, y);
    write(1, buf, strlen(buf));
}
