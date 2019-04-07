#include<stdio.h>
#include<stdlib.h>
void main()
{
<<<<<<< HEAD
	long long int i,j;
=======
	long long int i,j,k;
>>>>>>> b7f027ebd2ec50d29125c765c10bc359c1adfbca
	double A[250][250],B[250][250],C[250][250];
	for(i=0;i<250;i++)
	{
		for(j=0;j<250;j++)
		{
			for(k=0;k<250;k++)
			{
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}
}
