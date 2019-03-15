#include<stdio.h>
#include<stdlib.h>
#include<math.h>
long long int tagValue[1000000];
long long int setValue[1000000];
int lru(long long int tagValue[], long long int setValue[], long long int size, int numberOfWays)
{
	long long int hit=0, miss=0, i,j,k,temp1,temp2,flag;
	// number of sets, ways and block size are variable
	// block size if 64B and cache size if 1MB
	long long int cache_size = 1024*1024, no_of_blocks = cache_size/64, block_size = 64;
	long long int no_of_sets = no_of_blocks/numberOfWays;
	long long int value[16384];
	int valid[16384], tim[16384];
	// LRU algorithm
	for(i=0;i<no_of_blocks;i++)
	{
		value[i] = 0;
		valid[i] = 0;
		tim[i] = 0;
	}
	//printf("Starting of the algorithm\n");
	for(i=0;i<size;i++)
	{
		temp1 = setValue[i]*numberOfWays;
		temp2 = temp1+numberOfWays-1;
		flag = 0;
		// here replacement takes place in case of a miss and doesn't take place in case of a miss . hits and misses are counted.
		// setno. ranges from setvalue*numberofways to setvalue*numberofways + numberofways - 1
		for(j=temp1;j<=temp2;j++)
		{
			if(valid[j] == 1 && tagValue[i] == value[j])
			{
				// its a HIT
				++hit;
				printf("HIT\n");
				flag = 1;
				valid[j] = 1;
				tim[j] = i;
				break;
			}
		}
		if(flag!=1) // it is a miss
		{
			++miss;
			printf("MISS\n");
			flag = 0;
			for(j=temp1;j<=temp2;j++)
			{
				if(valid[j] == 0)
				{
					// allot this empty block to that instruction
					value[j] = tagValue[i];
					flag = 2;
					tim[j] = i;
					valid[j] = 1;
					break;
				}
			}
			if(flag != 2)
			{
				k = temp1;
				// replacement takes place as per the policy
				for(j=temp1;j<=temp2;j++)
				{
					if(tim[k]>tim[j])
						k = j;
				}
				// now we need to replace this block with index stored in 'k'
				value[k] = tagValue[i];
				tim[k] = i;
				valid[k] = 1;
				// block replaced and miss has also been incremented
			}
		}
	}
	//printf("No. of HIT = %lld and No. of MISS = %lld\n",hit,miss);
	return (float)(hit)/(hit+miss);
}
int main()
{
	long long int size = 20;
	int numberOfWays = 4;
	long long int i;
	tagValue[0]=0,tagValue[1]=1,tagValue[2]=2,tagValue[3]=2,tagValue[4]=4,tagValue[5]=6,
	tagValue[6]=0,tagValue[7]=0,tagValue[8]=2,tagValue[9]=2,tagValue[10]=4,tagValue[11]=6,
	tagValue[12]=0,tagValue[13]=0,tagValue[14]=2,tagValue[15]=2,tagValue[16]=4,tagValue[17]=6,
	tagValue[18]=0,tagValue[19]=0,tagValue[20]=2;
	setValue[0]=0,setValue[1]=1,setValue[2]=1,setValue[3]=2,setValue[4]=1,
	setValue[5]=1,setValue[6]=3,setValue[7]=1,setValue[8]=3,setValue[9]=1,
	setValue[10]=5,setValue[11]=1,setValue[12]=1,setValue[13]=10,setValue[14]=1,
	setValue[15]=1,setValue[16]=1,setValue[17]=1,setValue[18]=1,setValue[19]=1;
	lru(tagValue, setValue, size, numberOfWays);
    return 0;
    
}