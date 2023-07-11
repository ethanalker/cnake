#ifndef _CNAKE_H
#define _CNAKE_H

typedef struct {
    int x;
    int y;
} t_coord;

typedef struct cnakeNode {
    unsigned int x;
    unsigned int y;
    struct cnakeNode *next;
} t_node;

void init_cnake(unsigned int x, unsigned int y);
void add_head();
void del_tail();
void parse_key(const char c);

#endif // _CNAKE_H
