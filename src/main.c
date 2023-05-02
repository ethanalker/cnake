#include <ncurses.h>
#include <stdlib.h>

int main(void)
{
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    
    printw("hello");
    refresh();
    while(getch() != 'n');
    endwin();

    return 0;
}
