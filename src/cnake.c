#include <stdlib.h>
#include <stdint.h> // uint8_t
#include <stdio.h>
#include <string.h> // memset
#include <stddef.h> // size_t

#include "cnake.h"
#include "draw.h"
#include "io.h"

t_node *head;
t_node *tail;
t_node *free_node = NULL;

t_coord dir;

uint8_t (*board)[BOARD_COLS];

t_coord berry;

void init_cnake(unsigned int x, unsigned int y)
{
    head = malloc(sizeof(t_node));
    tail = head;

    head->x = x;
    head->y = y;
    head->next = NULL;

    dir.x = 1;
    dir.y = 0;

    board = malloc(sizeof(uint8_t[BOARD_ROWS][BOARD_COLS]));
    memset(board, 0, sizeof(uint8_t[BOARD_ROWS][BOARD_COLS]));

    set_board(x, y, 1);

    gen_berry();
    draw_head();
    refresh_screen();
}

void draw_berry(void)
{
    draw_str(berry.x, berry.y, "O", FONT_FX(RED_FG, BOLD));
}

void draw_head(void)
{
    draw_str(head->x, head->y, "0", FONT_FX(RESET));
}

void draw_tail(void)
{
    draw_str(tail->x, tail->y, " ", FONT_FX(RESET));
}

void clear_berry(void)
{
    draw_str(berry.x, berry.y, " ", FONT_FX(RESET));
    // this is just to move the cursor back to the head
    // the draw api is fucked, fix later
    draw_str(head->x, head->y, "", ""); 
}

// returns nonzero if berry grabbed
int check_berry()
{
    return (head->x == berry.x && head->y == berry.y);
}

void gen_berry(void)
{
    int x, y;
    do {
        x = rand() % (BOARD_COLS - 1) + 1;
        y = rand() % (BOARD_ROWS - 1) + 1;
    } while (!check_bounds(x, y) || get_board(x, y));

    berry.x = x;
    berry.y = y;

    draw_berry();
}

void set_board(size_t x, size_t y, uint8_t b)
{
    if (x >= BOARD_COLS || y >= BOARD_ROWS)
        return;
    board[y][x] = b;
}

uint8_t get_board(size_t x, size_t y)
{
    if (x >= BOARD_COLS || y >= BOARD_ROWS)
        return -1;
    return board[y][x];
}

void process_input(void)
{
    char c;
    while ((c = get_input())) {
        switch (c) {
            case 'h':
                if (!dir.x) {
                    dir.x = -1;
                    dir.y = 0;
                } else continue;
                break;
            case 'j':
                if (!dir.y) {
                    dir.x = 0;
                    dir.y = 1;
                } else continue;
                break;
            case 'k':
                if (!dir.y) {
                    dir.x = 0;
                    dir.y = -1;
                } else continue;
                break;
            case 'l':
                if (!dir.x) {
                    dir.x = 1;
                    dir.y = 0;
                } else continue;
                break;
            case 'q':
                exit(0);
                break;
        }
        break;
    }
}

// returns nonzero on valid position
int check_bounds(int x, int y)
{
    move_now(x, y);
    t_coord pos;
    do {
        pos = query_pos();
    } while (pos.x == 0 && pos.y == 0);

    return (pos.x == x && pos.y == y);
}

// returns nonzero on success
int add_head(void)
{
    t_node *next;
    if (free_node == NULL) {
        next = malloc(sizeof(t_node));
    } else {
        next = free_node;
        free_node = NULL;
    }

    head->next = next;
    next->x = head->x + dir.x;
    next->y = head->y + dir.y;
    next->next = NULL;

    head = next;

    // check self intersection or out of board bounds
    if (get_board(head->x, head->y))
        return 0;

    set_board(head->x, head->y, 1);
    draw_head();

    return check_bounds(head->x, head->y);
}

void del_tail(void)
{
    set_board(tail->x, tail->y, 0);
    draw_tail();
    t_node *prev_tail = tail;
    tail = prev_tail->next;

    free_node = prev_tail;
}
