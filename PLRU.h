#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct cacheSet2 cache2plru[512];
struct cacheSet4 cache4plru[256];
struct cacheSet8 cache8plru[128];
struct cacheSet16 cache16plru[64];

int node2=0,node4=0,node8=0,node16=0;
long long int cache_size = 1024*32;
int no_of_blocks=0;
int vreplace = 0;
int currLine = 0;
int i=0,j=0;
int counter;
int found2=-1,found4=-1,found8=-1,found16=-1;int first=0;


void init(int block_size,int n)
{
    no_of_blocks = cache_size/block_size;
    if(n==2)
    {
        for(i=0;i<512;i++)
        {
            for(j=0;j<2;j++)
            {
                cache2plru[i].c[j].valid=0;
                cache2plru[i].c[j].tag=-1;
            }

        }
    }
    if(n==4)
    {
        for(i=0;i<256;i++)
        {
            for(j=0;j<4;j++)
            {
                cache4plru[i].c[j].valid=0;
                cache4plru[i].c[j].tag=-1;
            }
        }
    }
    if(n==8)
    {
        for(i=0;i<128;i++)
        {
            for(j=0;j<8;j++)
            {
                cache8plru[i].c[j].valid=0;
                cache8plru[i].c[j].tag=-1;
            }
        }
    }
    if(n==16)
    {
        for(i=0;i<64;i++)
        {
            for(j=0;j<16;j++)
            {
                cache16plru[i].c[j].valid=0;
                cache16plru[i].c[j].tag=-1;
            }
        }
    }
}

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
            if(cache2plru[setValue].c[counter].tag==tagValue && cache2plru[setValue].c[counter].valid==1)
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
            currLine = 0;
			for(i=0; i<2 ;i++)
            {
                if(cache2plru[setValue].c[i].valid==0)
                {
                    vreplace=1;
                    currLine=i;
                    break;
                }
            }

			if(vreplace==0)
            {

				if (0 == node2)
					currLine = 0;
				if (1 == node2)
					currLine = 1;

			}

			cache2plru[setValue].c[currLine].tag=tagValue;
			cache2plru[setValue].c[currLine].valid=1;


			if (0 == currLine)
				node2 = 1;
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
            if(cache4plru[setValue].c[counter].tag==tagValue && cache4plru[setValue].c[counter].valid==1)
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
            currLine = 0;

			for(i=0;i<4;i++)
            {
                if(cache4plru[setValue].c[i].valid==0)
                {
                    vreplace=1;
                    currLine = i;
                    break;
                }
            }

			if(vreplace==0) {

				if (0 == (node4 & 6))
					currLine = 0;
				if (2 == (node4 & 6))
					currLine = 1;
				if (4 == (node4 & 5))
					currLine = 2;
				if (5 == (node4 & 5))
					currLine = 3;


			}

			cache4plru[setValue].c[currLine].tag=tagValue;
			cache4plru[setValue].c[currLine].valid=1;


			if (0 == currLine)
                node4 = (node4 & 1) | 6;
            if (1 == currLine)
                node4 = (node4 & 1) | 4;
            if (2 == currLine)
                node4 = (node4 & 2) | 1;
            if (3 == currLine)
                node4 = (node4 & 2) | 0;


            return 0;
		}


    }
    if(numberOfWays == 8)
    {

        found8 = -1;

		for (counter = 0; counter < 8 && found8< 0; counter++)
        {
            if(cache8plru[setValue].c[counter].tag==tagValue && cache8plru[setValue].c[counter].valid==1)
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

				found8 = 1;
				return 1;
            }
        }
        if (found8 == -1) {
            vreplace = 0;
            currLine = 0;

			for(i=0;i<8;i++)
            {
                if(cache8plru[setValue].c[i].valid==0)
                {
                    vreplace=1;
                    currLine = i;
                    break;
                }
            }

			if(vreplace==0) {

				if (0 == (node8 & 104))
					currLine = 0;
				if (8 == (node8 & 104))
					currLine = 1;
				if (32 == (node8 & 100))
					currLine = 2;
				if (36 == (node8 & 100))
					currLine = 3;
                if (64 == (node8 & 82))
					currLine = 4;
                if (66 == (node8 & 82))
					currLine = 5;
                if (80 == (node8 & 81))
					currLine = 6;
                if (81 == (node8 & 81))
					currLine = 7;


			}

			cache8plru[setValue].c[currLine].tag=tagValue;
			cache8plru[setValue].c[currLine].valid=1;


			if (0 == currLine)
                node8 = (node8 & 23) | 104;
            if (1 == currLine)
                node8 = (node8 & 23) | 96;
            if (2 == currLine)
                node8 = (node8 & 27) | 68;
            if (3 == currLine)
                node8 = (node8 & 27) | 64;
            if (4 == currLine)
                node8 = (node8 & 45) | 18;
            if (5 == currLine)
                node8 = (node8 & 45) | 16;
            if (6 == currLine)
                node8 = (node8 & 46) | 1;
            if (7 == currLine)
                node8 = (node8 & 46) | 0;
            return 0;
		}
    }
    if(numberOfWays == 16)
    {
        found16 = -1;

		for (counter = 0; counter < 16 && found16< 0; counter++)
        {
            if(cache16plru[setValue].c[counter].tag==tagValue && cache16plru[setValue].c[counter].valid==1)
            {
                if (0 == counter)
					node16 = (node16 & 23) | 104;
				if (1 == counter)
					node16 = (node16 & 23) | 96;
				if (2 == counter)
					node16 = (node16 & 27) | 616;
				if (3 == counter)
					node16 = (node16 & 27) | 64;
                if (4 == counter)
                    node16 = (node16 & 45) | 116;
                if (5 == counter)
                    node16 = (node16 & 45) | 16;
                if (6 == counter)
                    node16 = (node16 & 46) | 1;
                if (7 == counter)
                    node16 = (node16 & 46) | 0;
                if (8 == counter)
                    node16 = (node16 & 46) | 0;
                if (9 == counter)
                    node16 = (node16 & 46) | 0;
                if (10 == counter)
                    node16 = (node16 & 46) | 0;
                if (11 == counter)
                    node16 = (node16 & 46) | 0;
                if (12 == counter)
                    node16 = (node16 & 46) | 0;
                if (13 == counter)
                    node16 = (node16 & 46) | 0;
                if (14 == counter)
                    node16 = (node16 & 46) | 0;
                if (15 == counter)
                    node16 = (node16 & 46) | 0;


				found16 = counter;
				return 1;
            }
        }
        if (found16 == -1) {
            vreplace = 0;
            currLine = 0;

			for(i=0;i<16;i++)
            {
                if(cache16plru[setValue].c[i].valid==0)
                {
                    vreplace = 1;
                    currLine = i;
                }
            }

			if(vreplace=0) {
				// nodes=00x -> line 0
				// nodes=01x -> line 1
				// nodes=1x0 -> line 2
				// nodes=1x1 -> line 3
				if (0 == (node16 & 6))
					currLine = 0;
				else if (2 == (node16 & 6))
					currLine = 1;
				else if (4 == (node16 & 5))
					currLine = 2;
				else if (5 == (node16 & 5))
					currLine = 3;


			}

			cache4plru[setValue].c[currLine].tag=tagValue;


			if (0 == currLine)
                node16 = (node16 & 23) | 104;
            if (1 == currLine)
                node16 = (node16 & 23) | 96;
            if (2 == currLine)
                node16 = (node16 & 27) | 616;
            if (3 == currLine)
                node16 = (node16 & 27) | 64;
            if (4 == currLine)
                node16 = (node16 & 45) | 116;
            if (5 == currLine)
                node16 = (node16 & 45) | 16;
            if (6 == currLine)
                node16 = (node16 & 46) | 1;
            if (7 == currLine)
                node16 = (node16 & 46) | 0;
            if (8 == currLine)
                node16 = (node16 & 46) | 0;
            if (9 == currLine)
                node16 = (node16 & 46) | 0;
            if (10== currLine)
                node16 = (node16 & 46) | 0;
            if (11 == currLine)
                node16 = (node16 & 46) | 0;
            if (12 == currLine)
                node16 = (node16 & 46) | 0;
            if (14 == currLine)
                node16 = (node16 & 46) | 0;
            if (15 == currLine)
                node16 = (node16 & 46) | 0;
            return 0;
		}
    }



}
