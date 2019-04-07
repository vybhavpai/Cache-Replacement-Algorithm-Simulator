#include<bits/stdc++.h>


using namespace std;


static long long int **cacheNru; 
 	static int **validNru , **referencedNru ;

void check(long long int setNumber,int noOfWays)
{
	int i;
	//printf("inside check\n");
	for ( i = 0; i < noOfWays; ++i)
	{
		//printf("%d is way,%d is referencedNru\n",i,referencedNru[setNumber][i]);
		if(referencedNru[setNumber][i] == 0)
			return;
	}

	for ( i = 0; i < noOfWays; ++i)
	{
		referencedNru[setNumber][i] = 0;
	}


}


void replacement(long long int setNumber,long long int tagNumber,int noOfWays)
{
	int i;
	for(i=0;i<noOfWays;i++)
		if(validNru[setNumber][i] == 0)
		{
			validNru[setNumber][i] = 1;
			cacheNru[setNumber][i] = tagNumber;
			referencedNru[setNumber][i] = 1;
			check(setNumber,noOfWays);
			referencedNru[setNumber][i] = 1;
			return;
		}

	for(i=0;i<noOfWays;i++)
		if(referencedNru[setNumber][i] == 0)
		{
			// validNru[setNumber][i] = 1;
			referencedNru[setNumber][i] = 1;
			cacheNru[setNumber][i] = tagNumber;
			check(setNumber,noOfWays);
			referencedNru[setNumber][i] = 1;
			return;
		}

		
	

}
/*
void displ(int setno)
{
	for(int j=0;j<noOfWays;j++)
		printf("%d is way %lld is tag and %d is validNruity and %d is referencedNru\n",j,cacheNru[setno][j],validNru[setno][j],referencedNru[setno][j]);
		
		printf("\n\n");
}*/

int nru(long long int tagNumber, int setNumber,int noOfWays,int size)
{
	
	int i,j,hits=0, flag = 0;
	static int noOfSets = pow(2,15)/ (noOfWays*size);
	static int count = 0;
 	// cout << setNumber << "is setnumber and " << tagNumber<< "is tagnumber\n";
 	// printf("creating sets\n");

    

		// printf("sets initialized with memory\n");
	if(count == 0)
	{
	
	cacheNru = (long long int **)malloc(noOfSets * sizeof(long long int *)); 
 	validNru = (int **)malloc(noOfSets * sizeof(int *)); 
 	referencedNru = (int **)malloc(noOfSets * sizeof(int *));

 	for (i=0; i<noOfSets; i++) 
        { 
        	cacheNru[i] = (long long int *)malloc(noOfWays * sizeof(long long int));
        	validNru[i] = (int *)malloc(noOfWays * sizeof(int));
     		referencedNru[i] = (int *)malloc(noOfWays * sizeof(int));
        	   	
		}

	for (int i = 0; i < noOfSets; ++i)
	{
		for (int j = 0; j < noOfWays; ++j)
		{
			validNru[i][j] = 0;
			cacheNru[i][j]= 0;
			referencedNru[i][j] = 0;
		}

	}
	count = 1;

	}

	// printf("starting nru simulation\n");
	// for(i=0;i<size;i++)
	
	// flag = 0;

	// setNumber = setValue[i];
	// tagNumber = tagValue[i];
	//printf("%d is setNumber and %lld is tagNumber\n",setNumber,tagNumber );
	for(j=0;j<noOfWays;j++)
	{
		
		if(cacheNru[setNumber][j] == tagNumber)
		{
			
			// flag = 1;
			referencedNru[setNumber][j] = 1;
			check(setNumber,noOfWays);
			referencedNru[setNumber][j] = 1;	
			//displ(setNumber);
			//printf("\nhit at position %d\n",j);

			return 1;
		}
	
	}
	
		
	replacement(setNumber,tagNumber,noOfWays);
	
	return 0;
		
}

	

