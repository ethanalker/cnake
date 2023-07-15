#include <stdlib.h>
#include <time.h>
#include <sys/prctl.h> // prctl

#include "draw.h"
#include "term.h"
#include "io.h"
#include "utils.h"
#include "cnake.h"

int surplus;

void init(void)
{
    setup_termios();

    t_coord init_pos = query_pos();
    init_cnake(init_pos.x, init_pos.y > 1 ? init_pos.y - 1 : init_pos.y);
    surplus = 5;

    // allows any process to attach via ptrace, for debugging
    prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);

    inbuf_init();

    srand(time(NULL));
}

int main(void)
{
    init();

    while (1) {
        process_input();

        if (check_berry()) {
            surplus += 3;
            gen_berry();
        }

        if (surplus > 0) {
            surplus--;
        } else {
            del_tail();
        }

        if (!add_head()) break;

        refresh_screen();
        msleep(100);
    }

    return 0;
}
