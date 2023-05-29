#include <stdlib.h>

#include "cnake.h"
#include "draw.h"

Node *head;
Node *tail;
Coord dir;
// Coord berry;

void init_cnake(unsigned int x, unsigned int y)
{
    head = malloc(sizeof(Node));
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
    Node *next = malloc(sizeof(Node));

    head->next = next;
    next->x = head->x + dir.x;
    next->y = head->y + dir.y;

    head = next;

    draw_char(head->x, head->y, '0');
}

void del_tail(void)
{
    draw_char(tail->x, tail->y, ' ');
    Node *prev_tail = tail;
    tail = prev_tail->next;
    free(prev_tail);
}