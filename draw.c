#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#define C_W 10
#define C_H 17
#define T_  0xFFFFFFFF
#define BORD    0x0
#define X_  0xFFFF
#define READ_MOUSE  8

typedef unsigned int u32_t;
typedef unsigned short u16_t;
typedef unsigned char u8_t;

typedef struct
{
    int fd;
    struct fb_var_screeninfo fb_var;
    void * fb_mem;
    int w;
    int h;
    int bpp;
}fb_info_t, *pfb_info_t;

typedef struct
{
    int dx;
    int dy;
    int dz;
    int button;
}mevent_t;
mevent_t mevent;

static u32_t cursor_pixel[C_W*C_H] = 
{
    BORD, T_, T_, T_, T_, T_, T_, T_, T_, T_,
    BORD, BORD, T_, T_, T_, T_, T_, T_, T_, T_,
    BORD, X_, BORD, T_, T_, T_, T_, T_, T_, T_,
    BORD, X_, X_, BORD, T_, T_, T_, T_, T_, T_,
    BORD, X_, X_, X_, BORD, T_, T_, T_, T_, T_,
    BORD, X_, X_, X_, X_, BORD, T_, T_, T_, T_,
    BORD, X_, X_, X_, X_, X_, BORD, T_, T_, T_,
    BORD, X_, X_, X_, X_, X_, X_, BORD, T_, T_,
    BORD, X_, X_, X_, X_, X_, X_, X_, BORD, T_,
    BORD, X_, X_, X_, X_, X_, X_, X_, X_, BORD,
    BORD, X_, X_, X_, X_, X_, BORD, BORD, BORD,BORD,
    BORD, X_, X_, BORD, X_, X_, BORD, T_, T_, T_,
    BORD, X_, BORD, T_, BORD, X_, X_, BORD,T_, T_,
    BORD, BORD, T_, T_, BORD, X_, X_, BORD, T_, T_,
    T_, T_, T_, T_, T_, BORD, X_, X_, BORD, T_,
    T_, T_, T_, T_, T_, BORD, X_, X_, BORD, T_,
    T_, T_, T_, T_, T_, T_, BORD, BORD, T_, T_
};

void fb_pixel(pfb_info_t fb, int x, int y, u32_t color)
{
    u32_t *p;
    p =  (u32_t *)fb->fb_mem +x + y*fb->w;
    *p = color;
    return;
}

void mouse_draw(pfb_info_t pfb, int x, int y)
{
    int i, j;
    for (j = 0; j < C_H; j++) 
    {
        for (i = 0; i < C_W; i++) 
        {
            if(cursor_pixel[i + j*C_W] != T_)
                fb_pixel(pfb, x + i, y + j, cursor_pixel[i+j*C_W]);
        }
    }
}

int mouse_parse(int fd, mevent_t *mevent)
{
    u8_t buf[READ_MOUSE];
    int n;

    if((n = read(fd, buf, READ_MOUSE)) > 0)
    {
        mevent->button = buf[0]&0x07;
        mevent->dx = buf[1];
        mevent->dy = -buf[2];
        mevent->dz = buf[3];
    }
    else
        return -1;
    return 0;

}
int main(int argc, const char *argv[])
{
    fb_info_t fb;
    int fd, mfd, m_x, m_y;

    if((fd = open("/dev/fb0", O_RDWR)) < 0)
    {
        perror("open error:");
        exit(1);
    }
    if(-1 == ioctl(fd, FBIOGET_VSCREENINFO, &(fb.fb_var)))
    {
        perror("ioctl error:");
        exit(1);
    }
    fb.w = fb.fb_var.xres;
    fb.h = fb.fb_var.yres;
    fb.bpp = fb.fb_var.bits_per_pixel;
    fb.fd = fd;

    fb.fb_mem = mmap(NULL, fb.w*fb.h*fb.bpp/8, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(fb.fb_mem == MAP_FAILED)
    {
        perror("mmap error:");
        exit(1);
    }
    m_x = fb.w/2;
    m_y = fb.h/2;
    mouse_draw(&fb, m_x, m_y );
    mfd = open("/dev/input/mice", O_RDWR|O_NONBLOCK);
    if(mfd < 0)
    {
        perror("mice errror:");
        exit(1);
    }
    
    while(1){
        if((mouse_parse(mfd, &mevent)) == 0)
        {
            m_x += mevent.dx;
            m_y += mevent.dy;
            mouse_draw(&fb, m_x, m_y);
        }
    }
        close(fd);
        munmap(fb.fb_mem, fb.w*fb.h*fb.bpp/8);
        return 0;
    }
