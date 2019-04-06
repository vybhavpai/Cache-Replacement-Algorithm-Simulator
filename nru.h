#include<bits/stdc++.h>


using namespace std;


static long long int **cache; 
 	static int **valid , **referenced ;

void check(long long int setNumber,int noOfWays)
{
	int i;
	//printf("inside check\n");
	for ( i = 0; i < noOfWays; ++i)
	{
		//printf("%d is way,%d is referenced\n",i,referenced[setNumber][i]);
		if(referenced[setNumber][i] == 0)
			return;
	}

	for ( i = 0; i < noOfWays; ++i)
	{
		referenced[setNumber][i] = 0;
	}


}


void replacement(long long int setNumber,long long int tagNumber,int noOfWays)
{
	int i;
	for(i=0;i<noOfWays;i++)
		if(valid[setNumber][i] == 0)
		{
			valid[setNumber][i] = 1;
			cache[setNumber][i] = tagNumber;
			referenced[setNumber][i] = 1;
			check(setNumber,noOfWays);
			referenced[setNumber][i] = 1;
			return;
		}

	for(i=0;i<noOfWays;i++)
		if(referenced[setNumber][i] == 0)
		{
			// valid[setNumber][i] = 1;
			referenced[setNumber][i] = 1;
			cache[setNumber][i] = tagNumber;
			check(setNumber,noOfWays);
			referenced[setNumber][i] = 1;
			return;
		}

		
	

}
/*
void displ(int setno)
{
	for(int j=0;j<noOfWays;j++)
		printf("%d is way %lld is tag and %d is validity and %d is referenced\n",j,cache[setno][j],valid[setno][j],referenced[setno][j]);
		
		printf("\n\n");
}*/

int nru(long long int tagNumber, int setNumber,int noOfWays)
{
	int i,j,hits=0, flag = 0;
	static int noOfSets = pow(2,14)/ noOfWays;
	static int count = 0;
 	
 	// printf("creating sets\n");

    

		// printf("sets initialized with memory\n");
	if(count == 0)
	{
	
	cache = (long long int **)malloc(noOfSets * sizeof(long long int *)); 
 	valid = (int **)malloc(noOfSets * sizeof(int *)); 
 	referenced = (int **)malloc(noOfSets * sizeof(int *));

 	for (i=0; i<noOfSets; i++) 
        { 
        	cache[i] = (long long int *)malloc(noOfWays * sizeof(long long int));
        	valid[i] = (int *)malloc(noOfWays * sizeof(int));
     		referenced[i] = (int *)malloc(noOfWays * sizeof(int));
        	   	
		}

	for (int i = 0; i < noOfSets; ++i)
	{
		for (int j = 0; j < noOfWays; ++j)
		{
			valid[i][j] = 0;
			cache[i][j]= 0;
			referenced[i][j] = 0;
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
		
		if(cache[setNumber][j] == tagNumber)
		{
			
			// flag = 1;
			referenced[setNumber][j] = 1;
			check(setNumber,noOfWays);
			referenced[setNumber][j] = 1;	
			//displ(setNumber);
			//printf("\nhit at position %d\n",j);

			return 1;
		}
	
	}
	
		// if(!flag)
		
	replacement(setNumber,tagNumber,noOfWays);
	// displ(setNumber);
	//printf("\nmiss\n");
	return 0;
		
}

	



/*
int main(){
	
	int setValue[] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
	long long int tagValue[] = {500,501,500,502,501,502,500,503,500,503,504,500,501,505,500,506};

	printf("%f\n", nru(tagValue,setValue,16));

	//double hit = nru();
}
*/
