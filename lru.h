#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//long long int tagValue[1000000];
//long long int setValue[1000000];
int lru(long long int tagValue[], long long int setValue[], long long int size, int numberOfWays)
{
	double hit=0, miss=0;
	int i,j,k,temp1,temp2,flag;
	// number of sets, number of ways and set size are variable
	// block size is 64B and cache size is 1MB
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
	
	for(i=0;i<size;i++)
	{
		temp1 = setValue[i]*numberOfWays;
		temp2 = temp1+numberOfWays-1;
		flag = 0;		
		// setno. ranges from setvalue*numberofways to setvalue*numberofways + numberofways - 1
		for(j=temp1;j<=temp2;j++)
		{
			if(valid[j] == 1 && tagValue[i] == value[j])
			{
				// its a HIT
				++hit;
				//printf("HIT\n");
				flag = 1;
				valid[j] = 1;
				tim[j] = i;
				break;
			}
		}
		if(flag!=1) // it is a miss
		{
			++miss;
			//printf("MISS\n");
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
	return (hit)/(hit+miss); // returning hit ratio
}
/*
int main()
{
	long long int size;
	int numberOfWays;
	long long int i;
	
	lru(tagValue, setValue, size, numberOfWays);
    return 0;
    
}*/
