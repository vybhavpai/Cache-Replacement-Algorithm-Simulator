#include<stdio.h>
#include<stdlib.h>

#define MAX_RRPV 3

struct cacheLine
{
    int valid;
    long tag;
    int rrpv;
};
struct cacheSet2
{
    struct cacheLine c[2];
    int front, back;
};
struct cacheSet4
{
    struct cacheLine c[4];
    int front, back;
};
struct cacheSet8
{
    struct cacheLine c[8];
    int front, back;
};
struct cacheSet16
{
    struct cacheLine c[16];
    int front, back;
};
struct cacheSet2 cache2[8191];
struct cacheSet4 cache4[4096];
struct cacheSet8 cache8[2048];
struct cacheSet16 cache16[1024];
int miss, hit;
long long setNum,tag;

float calcforCacheset2(long long *indices, long long *tags, int size, int numOfWays)
{
    int i, j, count, no_cache_sets = 8191;

    //initialize maxRRPV i.e. to distant value 3
    for(int i=0; i < no_cache_sets; ++i)
    {
        for(int j=0; j < numOfWays; ++j)
        {
            cache2[i].c[j].rrpv = MAX_RRPV;
        }
    }

    // now check for every reference to the cache
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache2[setNum].c[j].valid == 1 && cache2[setNum].c[j].tag == tag)
            {
                printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                hit++;
                for(int k=0; k < no_cache_sets; ++k)
                {
                    for(int l=0; l < numOfWays; ++l)
                    {
                        if(cache2[k].c[l].rrpv < 3)
                        cache2[k].c[l].rrpv++;
                    }
                }
                cache2[setNum].c[i].rrpv = 0;
                break;
            }

            //Beginning with all misses
            else if (cache2[setNum].c[j].valid == 0)
            {
                printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                cache2[setNum].c[j].valid = 1;
                cache2[setNum].c[j].tag = tag;
                cache2[setNum].c[j].rrpv = MAX_RRPV;
                printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                miss++;
                break;
            }

            else
            {
                printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                cache2[setNum].c[j].rrpv = 0;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache2[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache2[setNum].c[i].tag = tag;
                            cache2[setNum].c[p].rrpv = 2;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache2[k].c[l].rrpv < 3)
                                    cache2[k].c[l].rrpv++;
                            }
                        }
                    }
                }
                
                count++;
            }

            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache2[setNum].back);
                miss++;
                cache2[setNum].c[cache2[setNum].back].tag = tag;
                cache2[setNum].c[cache2[setNum].back].valid = 1;
            }
        }
    }
    printf("Hit %d Miss %d", hit, miss);
    return ((float)hit / size);
}


float calcforCacheset4(long long *indices, long long *tags, int size, int numOfWays)
{
    int i, j, count, no_cache_sets = 4096;

    //initialize maxRRPV i.e. to distant value 3
    for(int i=0; i < no_cache_sets; ++i)
    {
        for(int j=0; j < numOfWays; ++j)
        {
            cache4[i].c[j].rrpv = MAX_RRPV;
        }
    }

    // now check for every reference to the cache
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache4[setNum].c[j].valid == 1 && cache4[setNum].c[j].tag == tag)
            {
                printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                hit++;
                for(int k=0; k < no_cache_sets; ++k)
                {
                    for(int l=0; l < numOfWays; ++l)
                    {
                        if(cache4[k].c[l].rrpv < 3)
                        cache4[k].c[l].rrpv++;
                    }
                }
                cache4[setNum].c[i].rrpv = 0;
                break;
            }

            //Beginning with all misses
            else if (cache4[setNum].c[j].valid == 0)
            {
                printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                cache4[setNum].c[j].valid = 1;
                cache4[setNum].c[j].tag = tag;
                cache4[setNum].c[j].rrpv = MAX_RRPV;
                printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                miss++;
                break;
            }

            else
            {
                printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                cache4[setNum].c[j].rrpv = 0;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache4[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache4[setNum].c[i].tag = tag;
                            cache4[setNum].c[p].rrpv = 2;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache4[k].c[l].rrpv < 3)
                                    cache4[k].c[l].rrpv++;
                            }
                        }
                    }
                }
                
                count++;
            }

            // if (cache4[i].c[j].valid == 0 || cache4[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache4[setNum].back);
                miss++;
                cache4[setNum].c[cache4[setNum].back].tag = tag;
                cache4[setNum].c[cache4[setNum].back].valid = 1;
            }
        }
    }
    printf("Hit %d Miss %d", hit, miss);
    return ((float)hit / size);
}

float calcforCacheset8(long long *indices, long long *tags, int size, int numOfWays)
{
    int i, j, count, no_cache_sets = 2048;

    //initialize maxRRPV i.e. to distant value 3
    for(int i=0; i < no_cache_sets; ++i)
    {
        for(int j=0; j < numOfWays; ++j)
        {
            cache8[i].c[j].rrpv = MAX_RRPV;
        }
    }

    // now check for every reference to the cache
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache8[setNum].c[j].valid == 1 && cache8[setNum].c[j].tag == tag)
            {
                printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                hit++;
                for(int k=0; k < no_cache_sets; ++k)
                {
                    for(int l=0; l < numOfWays; ++l)
                    {
                        if(cache8[k].c[l].rrpv < 3)
                        cache8[k].c[l].rrpv++;
                    }
                }
                cache8[setNum].c[i].rrpv = 0;
                break;
            }

            //Beginning with all misses
            else if (cache8[setNum].c[j].valid == 0)
            {
                printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                cache8[setNum].c[j].valid = 1;
                cache8[setNum].c[j].tag = tag;
                cache8[setNum].c[j].rrpv = MAX_RRPV;
                printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                miss++;
                break;
            }

            else
            {
                printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                cache8[setNum].c[j].rrpv = 0;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache8[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache8[setNum].c[i].tag = tag;
                            cache8[setNum].c[p].rrpv = 2;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache8[k].c[l].rrpv < 3)
                                    cache8[k].c[l].rrpv++;
                            }
                        }
                    }
                }
                
                count++;
            }

            // if (cache8[i].c[j].valid == 0 || cache8[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache8[setNum].back);
                miss++;
                cache8[setNum].c[cache8[setNum].back].tag = tag;
                cache8[setNum].c[cache8[setNum].back].valid = 1;
            }
        }
    }
    printf("Hit %d Miss %d", hit, miss);
    return ((float)hit / size);
}

float calcforCacheset16(long long *indices, long long *tags, int size, int numOfWays)
{
    int i, j, count, no_cache_sets = 1024;

    //initialize maxRRPV i.e. to distant value 3
    for(int i=0; i < no_cache_sets; ++i)
    {
        for(int j=0; j < numOfWays; ++j)
        {
            cache16[i].c[j].rrpv = MAX_RRPV;
        }
    }

    // now check for every reference to the cache
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache16[setNum].c[j].valid == 1 && cache16[setNum].c[j].tag == tag)
            {
                printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                hit++;
                for(int k=0; k < no_cache_sets; ++k)
                {
                    for(int l=0; l < numOfWays; ++l)
                    {
                        if(cache16[k].c[l].rrpv < 3)
                        cache16[k].c[l].rrpv++;
                    }
                }
                cache16[setNum].c[i].rrpv = 0;
                break;
            }

            //Beginning with all misses
            else if (cache16[setNum].c[j].valid == 0)
            {
                printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                cache16[setNum].c[j].valid = 1;
                cache16[setNum].c[j].tag = tag;
                cache16[setNum].c[j].rrpv = MAX_RRPV;
                printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                miss++;
                break;
            }

            else
            {
                printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                cache16[setNum].c[j].rrpv = 0;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache16[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache16[setNum].c[i].tag = tag;
                            cache16[setNum].c[p].rrpv = 2;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache16[k].c[l].rrpv < 3)
                                    cache16[k].c[l].rrpv++;
                            }
                        }
                    }
                }
                
                count++;
            }

            // if (cache16[i].c[j].valid == 0 || cache16[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache16[setNum].back);
                miss++;
                cache16[setNum].c[cache16[setNum].back].tag = tag;
                cache16[setNum].c[cache16[setNum].back].valid = 1;
            }
        }
    }
    printf("Hit %d Miss %d", hit, miss);
    return ((float)hit / size);
}


float srrip(long long *indices, long long *tags, int size, int numOfWays)
{
    float percentage;

    if (numOfWays == 2)
    {
        percentage = calcforCacheset2(indices, tags, size, numOfWays);
    }
    else if (numOfWays == 4)
    {
        percentage = calcforCacheset4(indices, tags, size, numOfWays);
    }
    else if (numOfWays == 8)
    {
        percentage = calcforCacheset8(indices, tags, size, numOfWays);
    }
    else
    {
        percentage = calcforCacheset16(indices, tags, size, numOfWays);
    }
    return percentage;
}

int main()
{
    printf("Enter size: ");
    int size;
    scanf("%d", &size);

    printf("Enter the indices: ");
    long long *indices = (long long *) malloc(sizeof(long long) * size);
    for(int i=0; i < size; ++i)
    {
        scanf("%lld", &indices[i]);
    }

    printf("Enter the number of ways: ");
    int numOfWays;
    scanf("%d", &numOfWays);

    printf("Enter the tags: ");
    long long *tags = (long long *) malloc(sizeof(long long) * size);
    for(int i=0; i < size; ++i)
    {
        scanf("%lld", &tags[i]);
    }

    printf("\n%f is the hit percentage\n", srrip(indices, tags, size, numOfWays));
}