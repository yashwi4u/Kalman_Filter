#include<stdio.h>
#include<stdbool.h>

float mat_mul(int m, int n, int mn, float mat1[m][mn], float mat2[mn][n], float res[m][n]) // To multiply two matrices
{
  int x, i, j;
  for (i=0; i<m; i++)
  {
    for (j=0; j<n; j++)
    {
      res[i][j]=0;
      for (x=0; x<mn; x++)
      {
        *(*(res+i) +j) += *(*(mat1+i) +x)**(*(mat2+x) +j);
      }
    }
  }
}
float mat_add(int row_r, int row_c, float mat1[row_r][row_c], float mat2[row_r][row_c])
{
  float res[row_r][row_c];
  for(int i=0; i<row_r; i++)
  {
    for(int j=0; j<row_c; j++) res[i][j] = mat1[i][j] + mat2[i][j] ;
  }
  return(res);
}
float mat_trans(int size, float A[][size], float B[][size]) // To get the transposed Matrix
{
    int i, j;
    for (i=0; i<size; i++)
    {
      for (j=0; j<size; j++) *(*(B+i)+j)=*(*(A+j)+i);
    }
}
void mat_print(int m, int n, float A[m][n]) // For printing Matrices
{
  for(int i = 0; i<m; i++)
  {
    for(int j = 0; j<n; j++) printf("%.2f ", *(*(A + i) + j));
    printf("\n");
  }
}
void mat_cofactor(int p,int q,int r,float A[r][r],float temp[r-1][r-1])
{
    int i=0, j=0;
    for(int row=0; row<r; row++) //  Copying into temporary matrix only those element which are not in given row and column
    {
        for(int col=0; col<r; col++)
        {
            if(row!=p && col!=q)
            {
                *(*(temp+i)+j) = *(*(A+row)+col);
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
}
float mat_det(int p, float A[p][p])// Recursive determinant function, p is current dimension of A[][]
{
    float res=0;
    if(p==1) return *(*(A+0)+0);
    float temp[p-1][p-1]; // To store cofactors
    float sign=1;  // To store sign multiplier
     // Iterate for each element of first row
    for(int f=0; f<p; f++)
    {
        mat_cofactor(0,f,p,A,temp);//(0,f)=coordinates, p=matrix size
        res+=sign**(*(A+0)+f)*mat_det(p-1,temp);
        sign=-sign;
    }
    return res;
}
void mat_adjoint(int p, float A[p][p],float adj[p][p])
{
    if(p==1)
    {
      *(*(adj+0)+0)=1;
      return;
    }
    int sign=1;
    float temp[p][p];
    for(int i=0; i<p; i++)
    {
        for(int j=0; j<p; j++)
        {
            mat_cofactor(i,j,p,A,temp);
            sign=((i+j)%2==0)? 1:-1;
            // Directly Interchanging rows and columns to get
            // the transpose of the cofactor matrix.
            *(*(adj+j)+i)=(sign)*(mat_det(p-1,temp));
        }
    }
}
float mat_inverse(int p,float A[p][p], float inverse[p][p])
{
  float det=mat_det(p,A);
  if(det==0)
  {
    printf("Singular matrix, can't find its inverse");
    return 0;
  }
  float adj[p][p];
  mat_adjoint(p,A,adj);
  for (int i=0; i<p; i++)
      for (int j=0; j<p; j++)
          *(*(inverse+i)+j) = (*(*(adj+i)+j))/det;
  return 1;
}

#define row_r 6
#define row_c 1
#define square 6

int main()
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

    flag = !flag; //For stopping while loop when no longer inputs are received.
  }

  printf("Out of while loop\n");
}
