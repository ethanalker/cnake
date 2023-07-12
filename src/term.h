#ifndef _TERM_H
#define _TERM_H

#define ALLOWED_KEYS "hjklq"
#define INBUF_SIZE 128

typedef struct inputnode {
    char c;
    struct inputnode *next;
} t_inputnode;

void reset_screen(void);
void reset_termios(void);
void setup_termios(void);
char read_key(void);
char get_input(void);
void build_inbuf(void);
void query_pos(size_t *x, size_t *y);

#endif // _TERM_H
