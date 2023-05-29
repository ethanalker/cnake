#ifndef _TERM_H
#define _TERM_H

#define ALLOWED_KEYS "hjklq"

void reset_screen(void);
void reset_termios(void);
void setup_termios(void);
char read_key(void);
char get_input(void);

#endif // _TERM_H
