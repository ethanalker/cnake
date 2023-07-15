#include <stdlib.h> // malloc, atexit
#include <unistd.h> // write
#include <termios.h> // tcsetattr, tcgetattr, etc

#include "term.h"
#include "utils.h"
#include "cnake.h"
#include "io.h"

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
VTIME: maximum time to wait before read() can return in deciseconds

*/

struct termios orig_termios;
struct termios blocking_read;
struct termios polling_read;

void clear_screen(void)
{
    write(1, "\x1b[2J", 4);
    write(1, "\x1b[H", 3);
}

void reset_termios(void)
{
    if (tcsetattr(0, TCSAFLUSH, &orig_termios) == -1) 
        die("tcsetattr");

    write(1, "\x1b[?25h", 6); // show cursor
    // clear_screen();
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
    raw.c_cc[VTIME] = 0;
    blocking_read = raw;

    raw.c_cc[VMIN] = 0;
    polling_read = raw;

    if (tcsetattr(0, TCSAFLUSH, &raw) == -1) die("tcsetattr");

    // hide cursor
    write(1, "\x1b[?25l", 6); 
}

void set_blocking(void)
{
    if (tcsetattr(0, TCSAFLUSH, &blocking_read) == -1) die("tcsetattr");
}

void set_polling(void)
{
    if (tcsetattr(0, TCSANOW, &polling_read) == -1) die("tcsetattr");
}
