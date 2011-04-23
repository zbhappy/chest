#ifndef _MAIN_H_
#define _MAIN_H_

#define ST_X    100
#define ST_Y    40
#define B_X     29
#define B_Y     24
#define SPACE   30
typedef unsigned int u_32_t;
typedef unsigned char u8_t;

typedef struct
{
    int w;
    int h;
    int bpp;

    void *memo;
}fbscr_t;

int init_screen(void);
int fb_one_pixel(int x, int y, u_32_t color);
int fb_line(int x1, int y1, int x2, int y2, u_32_t color);
int fb_circle(int x0, int y0, int r, u_32_t color);

#endif
