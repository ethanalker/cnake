#ifndef _CNAKE_H
#define _CNAKE_H

#include <stdint.h> // uint8_t
#include <stddef.h> // size_t

#define BOARD_COLS 192
#define BOARD_ROWS 128

typedef struct {
    int x;
    int y;
} t_coord;

typedef struct cnakeNode {
    int x;
    int y;
    struct cnakeNode *next;
} t_node;

void init_cnake(unsigned int x, unsigned int y);
void gen_berry(void);
int check_berry(void);
void draw_head(void);
void draw_tail(void);
void draw_berry(void);
void set_board(size_t x, size_t y, uint8_t b);
uint8_t get_board(size_t x, size_t y);
int check_bounds(int x, int y);
int add_head(void);
void del_tail(void);
void process_input(void);

#endif // _CNAKE_H
