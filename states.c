#include <stdio.h>
#include <stdbool.h>
#define row_r 6
#define row_c 1
#define square 6

void main()
{
  bool flag = true;
  int dt=1,ax=1,ay=1,az=1;
  float f[square][square] = { { 1,0,0,dt,0,0 }, { 0,1,0,0,dt,0 }, {0,0,1,0,0,dt}, {0,0,0,1,0,0}, {0,0,0,0,1,0}, {0,0,0,0,0,1} };
  float g[square][square] = {{0.5*(dt^2),0,0,0,0,0}, {0,0.5*(dt^2),0,0,0,0}, {0,0,0.5*(dt^2),0,0,0}, {dt,0,0,0,0,0}, {0,dt,0,0,0,0}, {0,0,dt,0,0,0}};
  float u[row_r][row_c] = { ax,ay,az,0,0,0 };
  float state_curr[row_r][row_c] = {1,1,1,1,1,1};
  float state_next[row_r][row_c] = {0,0,0,0,0,0};
  float state_prev[row_r][row_c] = {0,0,0,0,0,0};

  while(flag)
  {
    printf("Working \n");
    state_next=
    flag = !flag; //For stopping while loop when no longer inputs are received.
  }

  printf("Out of while loop\n");
}
