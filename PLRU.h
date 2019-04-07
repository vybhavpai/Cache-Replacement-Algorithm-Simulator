#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct cacheLine{
    long long int tag;
    int valid;
};

struct cacheSet2
{
    struct cacheLine c[2];

};
struct cacheSet4
{
    struct cacheLine c[4];

};
struct cacheSet8
{
    struct cacheLine c[4];

};
struct cacheSet16
{
    struct cacheLine c[16];
};
struct cacheSet2 cache2[8191];
struct cacheSet4 cache4[4096];
struct cacheSet8 cache8[2048];
struct cacheSet16 cache16[1024];
int node2=0,node4=0,node8=0,node16=0;
long long int cache_size = 1024*1024;
int no_of_blocks=0;
int vreplace = 0;
int currline=0;
void init(int block_size,int n)
{
    no_of_blocks = cache_size/block_size;
    if(n==2)
    {
        for(i=0;i<8191;i++)
        {
            for(j=0;j<2;j++)
            {
                cache2[i].c[j].valid=0;
                cache2[i].c[j].tag=-1;
            }

        }
    }
    if(n==4)
    {
        for(i=0;i<4096;i++)
        {
            for(j=0;j<4;j++)
            {
                cache4[i].c[j].valid=0;
                cache4[i].c[j].tag=-1;
            }
        }
    }
    if(n==8)
    {
        for(i=0;i<2048;i++)
        {
            for(j=0;j<8;j++)
            {
                cache8[i].c[j].valid=0;
                cache8[i].c[j].tag=-1;
            }
        }
    }
    if(n==16)
    {
        for(i=0;i<1024;i++)
        {
            for(j=0;j<16;j++)
            {
                cache16[i].c[j].valid=0;
                cache16[i].c[j].tag=-1;
            }
        }
    }
}
int i=0;
int counter;
int found2=-1,found4=-1,found8=-1,found16=-1;int first=0;
int plru(long long int tagValue, long long int setValue, int numberOfWays,int block_size)
{
    if(first==0)
    {
        init(block_size,numberOfWays);
        first=1;
    }
    if(numberOfWays==2)
    {

        found2 = -1;

		for (counter = 0; counter < 2 && found2 < 0; counter++)
        {
            if(cache2[setValue].c[counter].tag==tagValue && cache2[setValue].c[counter].valid==1)
            {
                if(counter==0)
                    node2=1;
                else
                    node2=0;
                found2=1;
                return 1;
            }
        }
        if (found2 == -1) {

			vreplace = 0;
            currline = 0;
			for(i=0; i<2 ;i++)
            {
                if(cache2[setValue].c[i].valid==0)
                {
                    vreplace=1;
                    currline=i;
                }
            }

			if(vreplace=0)
            {
				// nodes=00x -> line 0
				// nodes=01x -> line 1
				// nodes=1x0 -> line 2
				// nodes=1x1 -> line 3
				if (0 == node2)
					currLine = 1;
				else
					currLine = 0;

			}

			cache2[setValue].c[currline].tag=tagValue;

			// Update Nodes for last access (same as read, move to function):
			// nodes=00x -> line 0
			// nodes=01x -> line 1
			// nodes=1x0 -> line 2
			// nodes=1x1 -> line 3
			if (0 == currLine)
				node2=1;
			if (1 == currLine)
				node2 = 0;

            return 0;
		}


    }
    if(numberOfWays == 4)
    {
        found4 = -1;

		for (counter = 0; counter < 4 && found4< 0; counter++)
        {
            if(cache4[setValue].c[counter].tag==tagValue && cache4[setValue].c[counter].valid==1)
            {
                if (0 == counter)
					node4 = (node4 & 1) | 6;
				if (1 == counter)
					node4 = (node4 & 1) | 4;
				if (2 == counter)
					node4 = (node4 & 2) | 1;
				if (3 == counter)
					node4 = (node4 & 2) | 0;

				found4 = 1;
				return 1;
            }
        }
        if (found4 == -1) {
            vreplace = 0;
            currline = 0;

			for(i=0;i<4;i++)
            {
                if(cache4[setValue].c[i].valid==0)
                {
                    vreplace=1;
                    currline = i;
                }
            }

			if(vreplace=0) {
				// nodes=00x -> line 0
				// nodes=01x -> line 1
				// nodes=1x0 -> line 2
				// nodes=1x1 -> line 3
				if (0 == (node4 & 6))
					currLine = 0;
				else if (2 == (node4 & 6))
					currLine = 1;
				else if (4 == (node4 & 5))
					currLine = 2;
				else if (5 == (node4 & 5))
					currLine = 3;


			}

			cache4[setValue].c[currline].tag=tagValue;


			if (0 == counter)
                node4 = (node4 & 1) | 6;
            if (1 == counter)
                node4 = (node4 & 1) | 4;
            if (2 == counter)
                node4 = (node4 & 2) | 1;
            if (3 == counter)
                node4 = (node4 & 2) | 0;

            return 0;
		}


    }
    if(numberOfWays == 8)
    {

        found8 = -1;

		for (counter = 0; counter < 8 && found8< 0; counter++)
        {
            if(cache8[setValue].c[counter].tag==tagValue && cache8[setValue].c[counter].valid==1)
            {
                if (0 == counter)
					node8 = (node8 & 23) | 104;
				if (1 == counter)
					node8 = (node8 & 23) | 96;
				if (2 == counter)
					node8 = (node8 & 27) | 68;
				if (3 == counter)
					node8 = (node8 & 27) | 64;
                if (4 == counter)
                    node8 = (node8 & 45) | 18;
                if (5 == counter)
                    node8 = (node8 & 45) | 16;
                if (6 == counter)
                    node8 = (node8 & 46) | 1;
                if (7 == counter)
                    node8 = (node8 & 46) | 0;

				found8 = counter;
				return 1;
            }
        }
        if (found4 == -1) {
            vreplace = 0;
            currline = 0;

			for(i=0;i<8;i++)
            {
                if(cache8[setValue].c[i].valid==0)
                {
                    vreplace=1;
                    cache8[setValue].c
                }
            }

			if(vreplace=0) {
				// nodes=00x -> line 0
				// nodes=01x -> line 1
				// nodes=1x0 -> line 2
				// nodes=1x1 -> line 3
				if (0 == (node4 & 6))
					currLine = 0;
				else if (2 == (node4 & 6))
					currLine = 1;
				else if (4 == (node4 & 5))
					currLine = 2;
				else if (5 == (node4 & 5))
					currLine = 3;


			}

			cache4[setValue].c[currline].tag=tagValue;


			if (0 == counter)
                node4 = (node4 & 1) | 6;
            if (1 == counter)
                node4 = (node4 & 1) | 4;
            if (2 == counter)
                node4 = (node4 & 2) | 1;
            if (3 == counter)
                node4 = (node4 & 2) | 0;

            return 0;
		}
    }
    if(numberOfWays == 16)
    {

    }



}

