#ifndef _DRAW_H
#define _DRAW_H

#define WBUF_SIZE 100

void reset_buf(void);
void write_str(const char *s);
void write_chr(const char c);
void write_int(const int x);
void draw_char(const unsigned int x, const unsigned int y, const char c);
void draw_screen(void);

#endif // _DRAW_H