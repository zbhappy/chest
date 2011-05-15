#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#include<sys/mman.h>
#include<string.h>
#include<unistd.h>
#include "main.h"

fbscr_t fb_v;
extern char chess_board[B_X*B_Y];
char current_player;
extern u_32_t current_color;

int init_screen()
{
    int fd;
    struct fb_var_screeninfo fb_var;
    u_32_t *p = NULL;

    fd = open("/dev/fb0", O_RDWR);
    if(fd == -1)
    {
        perror("fb0");
        exit(0);
    }

    if( ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) == -1)
    {
        perror("ioctl");
        exit(0);
    }
    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    p =  mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    printf("x = %d y = %d, bits = %d\n", fb_var.xres, fb_var.yres, fb_var.bits_per_pixel);
    if(p == MAP_FAILED)
    {
        perror("map");
        exit(0);
    }

    fb_v.memo = p;

    memset(chess_board, 0, B_X*B_Y);
    memset((u_32_t*)fb_v.memo, 0, fb_v.w*fb_v.h*fb_v.bpp/8);
    current_player = 1;
    current_color = BLACK;


    close(fd);
    return 0;
}

int fb_one_pixel(int x, int y, u_32_t color)
{
    *((u_32_t*)fb_v.memo +x + y*fb_v.w) = color;
    return 0;
}
