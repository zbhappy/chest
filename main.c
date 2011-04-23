#include <stdio.h>
#include "main.h"

int main(int argc, const char *argv[])
{
    init_screen();
//    fb_one_pixel(512, 400, 0x000000ff);
//    fb_line(400, 700, 600, 0, 0x000000ff);
  //  fb_line(300, 0, 600, 700, 0x000000ff);
   // printf("hello world!\n");
   fb_circle(512, 415, 20, 0x000000ff);
    return 0;
}
