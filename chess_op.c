#include<stdio.h>
#include"main.h"

extern int mx;
extern int my;
char flag = 0;
u_32_t current_color = 0; 
char current_player = 0;

char chess_board[B_Y*B_X];

static u_32_t player1[21 * 17] = 
{
    T_, T_ ,T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    T_, T_, X_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    T_, X_, X_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, X_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,X_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,X_,X_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,X_,X_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,X_, T_, T_, T_,T_,T_,T_,X_,X_,X_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,X_, X_, T_, T_,T_,T_,X_,X_,X_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,X_, X_, T_, T_,T_,X_,X_,X_,T_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, X_, X_, T_,X_,X_,X_,T_,T_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, X_, X_, X_,X_,X_,T_,T_,T_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, X_, X_,X_,T_,T_,T_,T_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, X_,T_,T_,T_,T_,T_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, X_, X_, X_, X_,X_,X_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, X_, X_, X_, X_,X_,X_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_
};

static u_32_t player2[21 * 17] = 
{
    T_, T_ ,T_, X_, X_, X_,X_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    T_, T_, X_, X_, X_, X_,X_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    T_, X_, X_, X_, X_, X_,X_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, X_, T_, T_, X_,X_,X_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, T_, T_, T_, T_,T_,X_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,X_,
    X_, T_, T_, T_, T_, T_,T_,X_,X_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,X_,X_,
    T_, T_, T_, T_, T_, T_,X_,X_,X_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,X_,X_,X_,
    T_, T_, T_, T_, T_, T_,X_,X_,T_, T_ ,X_, T_, T_, T_,T_,T_,T_,X_,X_,X_,T_,
    T_, T_, T_, T_, T_, T_,X_,X_,T_, T_ ,X_, X_, T_, T_,T_,T_,X_,X_,X_,T_,T_,
    T_, T_, T_, T_, T_, X_,X_,X_,T_, T_ ,X_, X_, T_, T_,T_,X_,X_,X_,T_,T_,T_,
    T_, T_, T_, T_, X_, X_,X_,T_,T_, T_ ,T_, X_, X_, T_,X_,X_,X_,T_,T_,T_,T_,
    T_, T_, T_, X_, X_, X_,T_,T_,T_, T_ ,T_, X_, X_, X_,X_,X_,T_,T_,T_,T_,T_,
    T_, T_, T_, X_, X_, T_,T_,T_,T_, T_ ,T_, T_, X_, X_,X_,T_,T_,T_,T_,T_,T_,
    T_, T_, X_, X_, T_, T_,T_,T_,T_, T_ ,T_, T_, T_, X_,T_,T_,T_,T_,T_,T_,T_,
    T_, X_, X_, X_, T_, T_,T_,T_,T_, T_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, X_, X_, X_, X_,X_,X_,X_, X_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_,T_,
    X_, X_, X_, X_, X_, X_,X_,X_,X_, X_ ,T_, T_, T_, T_,T_,T_,T_,T_,T_,T_, T_
};


int check_one(int x, int y)
{
    int i = 0;
    int j = 0;
    int counter = 0;
    int who = 0;
    int m[4] = {1, 0, 1,  1};
    int n[4] = {0, 1, 1, -1};
    int sx = x;
    int sy = y;

    who = chess_board[x + y*B_X];
    if(who == 0)
    {
        return 0;
    }
    for(j = 0; j < 4; j++)
    {
            x = sx;
            y = sy;
            counter = 1;
            for(i = 1; i < 5; i++)
            {
                x += m[j];
                y += n[j];
                if(chess_board[x+y*B_X] == who)
                {
                    counter++;
                 }
                else
                {
                    break;
                }
            }
            if(counter == 5)
             {
                return who;
             }
    }
    return 0;
}
int check_win(void)
{
    int i = 0;
    int j = 0;
    int winner;
    
    for (j = 0; j < B_Y; j++) 
    {
        for (i = 0; i < B_X; i++) 
        {
            winner = check_one(i, j);
            if(winner > 0)
            {
                return winner;
            }
        }
    }
    return 0;
}
int chess_do(void)
{
    int x = mx;
    int y = my;
    int i;
    int j;

    int lx;
    int ly;
    int winner;

    if(flag == 0)
    {
        print_board();
        flag = 0xff;
        return 0;
    }

    if(x < ST_X || x > ST_X + SPACE*(B_X - 1))
    {   
        if((x > 42)&&(x < 78)&&(y > 82)&&(y < 118))
        {
            current_color = BLACK;
            current_player = 1;
        }
        else if((x > 42)&&(x < 78)&&(y > 182)&&(y < 218))
        {
            current_color = WHITE;
            current_player = 2;
        }

        return 0;
    }
    if(y < ST_Y || y > ST_Y + SPACE*(B_Y - 1))
    {
         return 0;
    }

    x = (x - ST_X)%SPACE;
    y = (y - ST_Y)%SPACE;

    if(x < SPACE/2)
    {
        x = mx - x;
    }
    else
    {
       x =  mx + (SPACE - x);
    }
    if(y < SPACE/2)
    {
        y = my - y;
    }
    else
    {
        y = my + (SPACE - y);
    }

    lx = (x - ST_X)/SPACE;
    ly = (y - ST_Y)/SPACE;

    chess_board[lx + ly*B_X] = current_player;
    fb_circle(x,  y, 13,  current_color);
    
    winner = check_win();
    if(winner > 0)
    {
        if(winner == 1)
        {
           for (j = 0; j < 17; j++) 
           {
               for (i = 0; i < 21; i++) 
               {
                    fb_one_pixel(60+i, 255+j, player1[i+j*21]);
               }
           }
        }
        else if(winner == 2)
        {
            
           for (j = 0; j < 17; j++) 
           {
               for (i = 0; i < 21; i++) 
               {
                    fb_one_pixel(60+i, 255+j, player2[i+j*21]);
               }
           }
        }
       // printf("player %d win\n", winner);
        return winner;
    }

    return 0;
}
