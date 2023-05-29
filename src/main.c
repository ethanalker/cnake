#include <stdlib.h> // rand

#include "draw.h"
#include "term.h"
#include "utils.h"
#include "cnake.h"

int main(void)
{
    setup_termios();
    init_cnake(50, 50);

    while (1) {
        char c = get_input();

        parse_key(c);
        add_head();

        if ((rand() % 2) == 1) {
            del_tail();
        }

        draw_screen();
        msleep(100);

        // when it comes time to check out of bounds, query position after movement and check if it matches the stored position
        // if it doesn't, that means the move wasn't successful and you hit a wall
        // this means it'll dynamically resize the window as the window size changes
        // you can also kill yourself by shrinking the window, which is a feature not a bug. 

    }

    return 0;
}
