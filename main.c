#include <stdio.h>
#include<unistd.h>
#include "main.h"

int main(int argc, const char *argv[])
{
    init_screen();
//    fb_one_pixel(512, 400, 0x000000ff);
//    fb_line(400, 700, 600, 0, 0x000000ff);
  //  fb_line(300, 0, 600, 700, 0x000000ff);
   // printf("hello world!\n");
//   fb_circle(512, 415, 20, 0x000000ff);
//   print_board();
//   save_bg(512, 367);
  // draw_cursor(512, 367);
   //sleep(2);
   //restore(512, 367);
   //draw_cursor(400, 300);
     mouse_doing();
    return 0;
}
