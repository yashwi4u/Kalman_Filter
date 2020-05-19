#include<stdio.h>

void main()
{
	int mat[3][3], i, j;
	float determinant = 0.00;
  float inv[3][3];

	printf("Enter elements of matrix row wise:\n");
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++) scanf("%d", &mat[i][j]);

	printf("\nGiven matrix is:");
	for(i = 0; i < 3; i++)
	{
		printf("\n");
		for(j = 0; j < 3; j++) printf("%d\t", mat[i][j]);
	}
	for(i = 0; i < 3; i++) //finding determinant
		determinant = determinant + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));
	printf("\n\ndeterminant: %f\n", determinant);

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			//inv[i][j] = (float)((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ (float)determinant ;
			printf("%.2f\n%.2f\n%.2f\n%.2f\n%f\n\n",mat[(j+1)%3][(i+1)%3], mat[(j+2)%3][(i+2)%3], mat[(j+1)%3][(i+2)%3], mat[(j+2)%3][(i+1)%3], determinant);
			printf("\n");
		}
	}

	// printf("\nInverse of matrix is: \n");
	// for(i = 0; i < 3; i++)
	// {
	// 	printf("\n");
	// 	for(j = 0; j < 3; j++) printf("%d\t", inv[i][j]);
	// }
}
