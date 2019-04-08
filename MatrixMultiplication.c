//Ankit Jain (17CO208)
//Program for generating trace file for matrix multiplication for row-major accesses only
#include<stdio.h>
#define N 250
double X[N][N], Y[N][N], Z[N][N];
void main()
{
	int i,j,k;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			//assigning random values to both Arrays
			Y[i][j] = i+j;
			Z[i][j] = i-j;
		}
	for(i=0;i<N;i++)
		for(k=0;k<N;k++)
			for(j=0;j<N;j++)
				X[i][j] += Y[i][k] * Z[k][j];
}
