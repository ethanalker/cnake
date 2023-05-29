#include <stdlib.h> // atexit
#include <unistd.h> // write
#include <termios.h> // tcsetattr, tcgetattr, etc
#include <errno.h> // errno
#include <string.h> // strchr

#include "term.h"
#include "utils.h"

/*

input flags:
BRKINT: causes a break condition to send SIGINT to the program
INPCK: enables parity checking, most likely doesn't apply to modern temrinals
ISTRIP: strips the eigth bit of each input byte
ICRNL: causes carriage returns to be translated to newlines (CR to NL)
IXON: enables software flow control (Ctrl-S and Ctrl-Q)

output flags:
OPOST: enables output processing (NL to CRNL)

local flags:
ECHO: enables terminal echo
ICANON: enables canonical mode (reading bytes instead of lines)
IEXTEN: enables input processing (Ctrl-V to escape characters)
ISIG: enables signals from keypresses (Ctrl-C and Ctrl-Z)

control flags:
CS8: sets character size to eight bits per byte

control characters:
VMIN: minimum number of bytes before read() can return
VTIME: maximum time to wait before read() can return in 100 milliseconds

*/

struct termios orig_termios;

void reset_screen(void)
{
    write(1, "\x1b[2J", 4);
    write(1, "\x1b[H", 3);
}

void reset_termios(void)
{
    if (tcsetattr(0, TCSAFLUSH, &orig_termios) == -1) 
        die("tcsetattr");

    write(1, "\x1b[?25h", 6); // show cursor
    reset_screen();
}

void setup_termios(void)
{
    if (tcgetattr(0, &orig_termios) == -1) die("tcgetattr");
    atexit(reset_termios);

    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSAFLUSH, &raw) == -1) die("tcsetattr");

    write(1, "\x1b[?25l", 6); // hide cursor
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

char get_input(void)
{
    char c;
    while ((c = read_key())) {
        if (strchr(ALLOWED_KEYS, c)) break;
    }
    return c;
}
