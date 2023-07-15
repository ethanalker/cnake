#ifndef _TERM_H
#define _TERM_H

#define ALLOWED_KEYS "hjklq"

void clear_screen(void);
void reset_termios(void);
void setup_termios(void);
void set_blocking(void);
void set_polling(void);

#endif // _TERM_H
