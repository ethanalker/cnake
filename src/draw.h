#ifndef _DRAW_H
#define _DRAW_H

#define WBUF_SIZE 128

// fg colors
#define BLACK_FG 30
#define RED_FG 31
#define GREEN_FG 32
#define YELLOW_FG 33
#define BLUE_FG 34
#define MAGENTA_FG 35
#define CYAN_FG 36
#define WHITE_FG 37
#define DEFAULT_FG 39
// bg colors
#define BLACK_BG 40
#define RED_BG 41
#define GREEN_BG 42
#define YELLOW_BG 43
#define BLUE_BG 44
#define MAGENTA_BG 45
#define CYAN_BG 46
#define WHITE_BG 47
#define DEFAULT_BG 49
// general fx
#define RESET 0
#define BOLD 1
#define BOLD_OFF 21
#define NORMAL_INTENSITY 22

// thanks john xoxo https://stackoverflow.com/a/76691776/20823202
// Helper macros:
#define JOIN_4(a1, a2, a3, a4, ...) #a1 ";" #a2 ";" #a3 ";" #a4
#define JOIN_3(a1, a2, a3, ...)     #a1 ";" #a2 ";" #a3
#define JOIN_2(a1, a2, ...)         #a1 ";" #a2
#define JOIN_1(a1, ...)             #a1
#define SEMI_LIST(a1, a2, a3, a4, a5, ...) JOIN ## a5 (a1, a2, a3, a4)

// Main macro
// Use this with at least one and no more than four arguments:
#define FONT_FX(...) "\x1b[" SEMI_LIST(__VA_ARGS__, _4, _3, _2, _1) "m"

void reset_buf(void);
void write_str(char **p, const char *s);
void write_int(char **p, const int x);
void move_cursor(char **p, const unsigned int x, const unsigned int y);
void draw_str(const unsigned int x, const unsigned int y, const char *s, const char *fx);
void refresh_screen(void);
void move_now(const unsigned int x, const unsigned int y);

#endif // _DRAW_H