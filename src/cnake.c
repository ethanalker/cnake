#include <stdlib.h>

#include "cnake.h"
#include "draw.h"

t_node *head;
t_node *tail;
t_node *free_tail = NULL;
t_coord dir;
// t_coord berry;

void init_cnake(unsigned int x, unsigned int y)
{
    head = malloc(sizeof(t_node));
    tail = head;

    head->x = x;
    head->y = y;
    head->next = NULL;

    dir.x = 1;
    dir.y = 0;
}

void parse_key(const char c)
{
    switch (c) {
        case 'h':
            if (!dir.x) {
                dir.x = -1;
                dir.y = 0;
            }
            break;
        case 'j':
            if (!dir.y) {
                dir.x = 0;
                dir.y = 1;
            }
            break;
        case 'k':
            if (!dir.y) {
                dir.x = 0;
                dir.y = -1;
            }
            break;
        case 'l':
            if (!dir.x) {
                dir.x = 1;
                dir.y = 0;
            }
            break;
        case 'q':
            exit(0);
            break;
    }
}

void add_head(void)
{
    t_node *next;
    if (free_tail == NULL) {
        next = malloc(sizeof(t_node));
    } else {
        next = free_tail;
        free_tail = NULL;
    }

    head->next = next;
    next->x = head->x + dir.x;
    next->y = head->y + dir.y;
    next->next = NULL;

    head = next;

    draw_char(head->x, head->y, '0');
}

void del_tail(void)
{
    draw_char(tail->x, tail->y, ' ');
    t_node *prev_tail = tail;
    tail = prev_tail->next;

    free_tail = prev_tail;
}
