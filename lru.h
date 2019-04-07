#include<stdio.h>
#include<stdlib.h>
#include<math.h>
long long int tagValue;
long long int setValue;
long long int value[4096];
int valid[4096], tim[4096];
static int count=0;
int lru(long long int tagValue, long long int setValue, long long int size, int numberOfWays, long long int block_size)
{
	long long int cache_size = 1024*256, no_of_blocks = cache_size/block_size;
	long long int i,j,k,temp1,temp2,flag;
	long long int no_of_sets = no_of_blocks/numberOfWays;
	if(count == 0)
	{	
		// initialize this only once
		for(i=0;i<no_of_blocks;i++)
		{
			value[i] = 0;
			valid[i] = 0;
			tim[i] = 0;
		} // create only once
		count = 1;
	}	
	// LRU algorithm
	temp1 = setValue*numberOfWays;
	temp2 = temp1+numberOfWays-1;
	flag = 0;		
	// setno. ranges from setvalue*numberofways to setvalue*numberofways + numberofways - 1
	for(j=temp1;j<=temp2;j++)
	{
		if(valid[j] == 1 && tagValue == value[j])
		{
			valid[j] = 1;
			tim[j] = i;
			return 1;                // return HIT
		}
	}
	flag = 0;
	for(j=temp1;j<=temp2;j++)
	{
		if(valid[j] == 0)
		{
			// allot this empty block to that instruction
			value[j] = tagValue;
			flag = 2;
			tim[j] = i;
			valid[j] = 1;
			return 0;               // return cold MISS
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
		value[k] = tagValue;
		tim[k] = i;
		valid[k] = 1;
		// block replaced and miss has also been incremented
		return 0;                      // return MISS
	}
}
