#ifndef _IO_H
#define _IO_H

#include "cnake.h"

#define INBUF_SIZE 128

void inbuf_init(void);
char *inbuf_next(char *p);
void inbuf_write(char c);
char inbuf_read(void);
char read_key(void);
void dump_to_inbuf(void);
char get_input(void);
t_coord query_pos(void);

#endif // _IO_H
