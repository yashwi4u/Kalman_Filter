#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct array
{
    int row;
    int column;
    float **arr;
};
struct array mat_define(int row, int column)
{
    struct array f;
    f.row = row;
    f.column = column;
    f.arr = (float **)malloc((row) * sizeof(float *));
    for(int i=0; i<row; i++) // Allocate memory for the array
    {
        f.arr[i] = (float *)malloc((column) * sizeof(float));
    }
    for(int i=0; i<row; i++) // Intialize the array with all elements as 0
    {
      for(int j=0; j<column; j++) f.arr[i][j]=0;
    }
    return f;
}
void mat_print(struct array result) // For printing Matrices
{
  for (int i=0; i<result.row; i++)
  {
    for (int j=0; j<result.column; j++) printf("%.2f ",result.arr[i][j]);
    printf("\n");
  }
}
struct array mat_mul(struct array mat1,struct array mat2)
{
  struct array res = mat_define(mat1.row,mat2.column);
  if(mat1.row==mat2.column)
  {
    printf("Cannot perform Multiplication");
    return(res);
  }
  int x,i,j;
  for (i=0; i<mat1.row; i++)
  {
    for (j=0; j<mat2.column; j++)
    {
      for (x=0; x<mat1.column; x++)
      {
        res.arr[i][j] += mat1.arr[i][x]*mat2.arr[x][j];
      }
    }
  }
  return(res);
}
struct array mat_add(struct array mat1,struct array mat2)
{
  struct array res = mat_define(mat1.row,mat1.column);
  for(int i=0; i<mat1.row; i++)
  {
    for(int j=0; j<mat1.column; j++) res.arr[i][j] = mat1.arr[i][j] + mat2.arr[i][j] ;
  }
  return(res);
}
struct array mat_trans(struct array a) // To get the transposed Matrix
{
  struct array res = mat_define(a.row, a.column);
  for (int i=0; i<a.row; i++)
  {
    for (int j = 0; j < a.column; j++) res.arr[j][i] = a.arr[i][j];
  }
  return res;
}
struct array mat_cofactor(int p,int q,struct array mat)
{
    int i=0, j=0,r=mat.row;
    struct array temp = mat_define(r-1,r-1);
    for(int row=0; row<mat.row; row++) //Copying into temporary matrix only those element which are not in given row and column
    {
        for(int col=0; col<mat.row; col++)
        {
            if(row!=p && col!=q)
            {
                temp.arr[i][j] = mat.arr[row][col];
                j++;
                // Row is filled, so increase row index and
                // reset col index
                if(j==r-1)
                {
                  j=0;
                  i++;
                }
            }
        }
    }
    return(temp);
}
float mat_det(struct array mat)// Recursive determinant function, p is current dimension of A[][]
{
    float res=0;
    int p=mat.row;
    if(mat.row==1) return mat.arr[0][0];
    struct array temp = mat_define(p-1,p-1); // To store cofactors
    float sign=1;  // To store sign multiplier
     // Iterate for each element of first row
    for(int f=0; f<p; f++)
    {
        temp = mat_cofactor(0,f,mat);//(0,f)=coordinates, p=matrix size
        res+=sign*mat.arr[0][f]*mat_det(temp);
        sign=-sign;
    }
    return(res);
}
struct array mat_adjoint(struct array mat)
{
  int p = mat.row;
  struct array adj = mat_define(p,p);
  if(p==1)
  {
    adj.arr[0][0]=1;
    return(adj);
  }
  int sign=1;
  struct array temp = mat_define(p,p);
  for(int i=0; i<p; i++)
  {
    for(int j=0; j<p; j++)
    {
      temp = mat_cofactor(i,j,mat);
      sign=((i+j)%2==0)? 1:-1;
      // Directly Interchanging rows and columns to get
      // the transpose of the cofactor matrix.
      adj.arr[j][i]=(sign)*(mat_det(temp));
    }
  }
  return(adj);
}
struct array mat_inverse(struct array mat)
{
  int p=mat.row;
  struct array inverse = mat_define(p,p);
  struct array adj = mat_define(p,p);
  float det=mat_det(mat);
  if(det==0)
  {
    printf("Singular matrix, can't find its inverse");
    return(inverse);
  }
  adj = mat_adjoint(mat);
  for (int i=0; i<p; i++)
      for (int j=0; j<p; j++)
          inverse.arr[i][j] = adj.arr[i][j]/det;
  return(inverse);
}

#define row_r 6 // row_r means number of rows in row vector
#define row_c 1 // row_c means number of columns in row vector
#define square 6 // It is given to both number of rows and columns in square matrix

void main()
{
  float dt=1;bool flag = true;
  float ax=1,ay=1,az=1;
  struct array I = mat_define(square,square); // I(6x6) matrix
  struct array F = mat_define(square,square); // I(6x6) matrix
  for(int i=0; i<I.row; i++) // To make an identity matrix
  {
    I.arr[i][i] = 1;
    F.arr[i][i] = 1;
  }
  F.arr[0][3] = F.arr[1][4] = F.arr[2][5] = dt; // Defining F
  struct array G = mat_define(square,square); // Defining G
  G.arr[0][0]=G.arr[1][1]=G.arr[2][2]=(0.5*dt*dt);
  G.arr[3][0]=G.arr[4][1]=G.arr[5][2]=dt;

  struct array U = mat_define(row_r,row_c); // Defining control vector
  U.arr[0][0]=ax; U.arr[1][0]=ay; U.arr[2][0]=az;
  struct array state = mat_define(row_r,row_c); //Defining current state
  struct array P = mat_define();
  state.arr[0][0]=state.arr[1][0]=state.arr[2][0]=state.arr[3][0]=state.arr[4][0]=state.arr[5][0]=1;

  struct array state_prev = mat_define(row_r,row_c);
  struct array state_next = mat_define(row_r,row_c);
  while(flag)
  {
    printf("Working \n");
    state_next = mat_add(mat_mul(F,state),mat_mul(G,U));
    mat_print(state_next);

    flag = !flag; //For stopping while loop when no longer inputs are received.
  }
}
