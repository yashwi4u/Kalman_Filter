#include<stdio.h>

struct array
{
    int row;
    int column;
    float arr[row][column];
};

void main()
{
  struct array mat1;
  mat1.row = mat1.column = 6;
  
}
