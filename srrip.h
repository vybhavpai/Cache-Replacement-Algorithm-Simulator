#include<stdio.h>
#include<stdlib.h>

#define MAX_RRPV 3

struct cacheLineSRRIP
{
    int valid;
    long tag;
    int rrpv;
};
struct cacheSet2SRRIP
{
    struct cacheLineSRRIP c[2];
    int front, back;
};
struct cacheSet4SRRIP
{
    struct cacheLineSRRIP c[4];
    int front, back;
};
struct cacheSet8SRRIP
{
    struct cacheLineSRRIP c[8];
    int front, back;
};
struct cacheSet16SRRIP
{
    struct cacheLineSRRIP c[16];
    int front, back;
};
struct cacheSet2SRRIP cache2srrip[33000];
struct cacheSet4SRRIP cache4srrip[33000];
struct cacheSet8SRRIP cache8srrip[33000];
struct cacheSet16SRRIP cache16srrip[33000];

static int initializeCacheSetSRRIP = 0;

int calcforCacheset2srrip(long long indices, long long tags, int size, int numOfWays, int blocksize)
{
    int cache_size = 32*1024, no_cache_blocks = cache_size/blocksize;
    int i, j, count, no_cache_sets = no_cache_blocks/numOfWays;
    long long setNum,tag;

    if(initializeCacheSetSRRIP == 0)
    {
        // initialize maxRRPV i.e. to distant value 3
        for(int i=0; i < no_cache_sets; ++i)
        {
            for(int j=0; j < numOfWays; ++j)
            {
                cache2srrip[i].c[j].rrpv = MAX_RRPV;
            }
        }
        printf("Cache RRPV Initialization done\n");
        initializeCacheSetSRRIP = 1;
    }
    
    // now check for every reference to the cache
        setNum = indices;
        tag = tags;
        //printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            // if cache block is valid and tag matches then we have a hit
            if (cache2srrip[setNum].c[j].valid == 1 && cache2srrip[setNum].c[j].tag == tag)
            {
                //printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                for(long long int k=0; k < no_cache_sets; ++k)
                {
                    //printf("DEBUG: k = %lld Inside LOOP1 the updating cache rrpv values\n", k);
                    for(long long int l=0; l < numOfWays; ++l)
                    {
                        if(cache2srrip[k].c[l].rrpv < 3)
                        cache2srrip[k].c[l].rrpv++;
                        //printf("DEBUG: l = %lld Inside LOOP2 the updating cache rrpv values\n", l);
                    }
                }
                cache2srrip[setNum].c[i].rrpv = 0;
                return 1;
            }

            //Beginning with all misses - that is when the cache is being warmed up.
            else if (cache2srrip[setNum].c[j].valid == 0)
            {
                //printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                cache2srrip[setNum].c[j].valid = 1;
                cache2srrip[setNum].c[j].tag = tag;
                cache2srrip[setNum].c[j].rrpv = MAX_RRPV;
                //printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                return 0;
            }

            //Cache miss at set and cache line is valid
            else
            {
                //printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                count++;
            }

            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                //printf("All cache lines in the set checked and no match so replacement will be performed\n");
                cache2srrip[setNum].c[cache2srrip[setNum].back].tag = tag;
                cache2srrip[setNum].c[cache2srrip[setNum].back].valid = 1;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache2srrip[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache2srrip[setNum].c[i].tag = tag;
                            cache2srrip[setNum].c[p].rrpv = 2;
                            return 0;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache2srrip[k].c[l].rrpv < 3)
                                    cache2srrip[k].c[l].rrpv++;
                            }
                        }
                    }
                }
            }
        }
    //printf("Hit %d Miss %d", hit, miss);
    return 0;
}


int calcforCacheset4srrip(long long indices, long long tags, int size, int numOfWays, int blocksize)
{
    int cache_size = 32*1024, no_cache_blocks = cache_size/blocksize;
    int i, j, count, no_cache_sets = no_cache_blocks/numOfWays;
    long long setNum,tag;

    if(initializeCacheSetSRRIP == 0)
    {
        // initialize maxRRPV i.e. to distant value 3
        for(int i=0; i < no_cache_sets; ++i)
        {
            for(int j=0; j < numOfWays; ++j)
            {
                cache4srrip[i].c[j].rrpv = MAX_RRPV;
            }
        }
        printf("Cache RRPV Initialization done\n");
        initializeCacheSetSRRIP = 1;
    }
    
    // now check for every reference to the cache
        setNum = indices;
        tag = tags;
        //printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            // if cache block is valid and tag matches then we have a hit
            if (cache4srrip[setNum].c[j].valid == 1 && cache4srrip[setNum].c[j].tag == tag)
            {
                //printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                for(long long int k=0; k < no_cache_sets; ++k)
                {
                    //printf("DEBUG: k = %lld Inside LOOP1 the updating cache rrpv values\n", k);
                    for(long long int l=0; l < numOfWays; ++l)
                    {
                        if(cache4srrip[k].c[l].rrpv < 3)
                        cache4srrip[k].c[l].rrpv++;
                        //printf("DEBUG: l = %lld Inside LOOP2 the updating cache rrpv values\n", l);
                    }
                }
                cache4srrip[setNum].c[i].rrpv = 0;
                return 1;
            }

            //Beginning with all misses - that is when the cache is being warmed up.
            else if (cache4srrip[setNum].c[j].valid == 0)
            {
                //printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                cache4srrip[setNum].c[j].valid = 1;
                cache4srrip[setNum].c[j].tag = tag;
                cache4srrip[setNum].c[j].rrpv = MAX_RRPV;
                //printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                return 0;
            }

            //Cache miss at set and cache line is valid
            else
            {
                //printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                count++;
            }

            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                //printf("All cache lines in the set checked and no match so replacement will be performed\n");
                cache4srrip[setNum].c[cache2srrip[setNum].back].tag = tag;
                cache4srrip[setNum].c[cache2srrip[setNum].back].valid = 1;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache4srrip[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache4srrip[setNum].c[i].tag = tag;
                            cache4srrip[setNum].c[p].rrpv = 2;
                            return 0;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache4srrip[k].c[l].rrpv < 3)
                                    cache4srrip[k].c[l].rrpv++;
                            }
                        }
                    }
                }
            }
        }
    //printf("Hit %d Miss %d", hit, miss);
    return 0;
}

int calcforCacheset8srrip(long long indices, long long tags, int size, int numOfWays, int blocksize)
{
    int cache_size = 32*1024, no_cache_blocks = cache_size/blocksize;
    int i, j, count, no_cache_sets = no_cache_blocks/numOfWays;
    long long setNum,tag;

    if(initializeCacheSetSRRIP == 0)
    {
        // initialize maxRRPV i.e. to distant value 3
        for(int i=0; i < no_cache_sets; ++i)
        {
            for(int j=0; j < numOfWays; ++j)
            {
                cache8srrip[i].c[j].rrpv = MAX_RRPV;
            }
        }
        printf("Cache RRPV Initialization done\n");
        initializeCacheSetSRRIP = 1;
    }
    
    // now check for every reference to the cache
        setNum = indices;
        tag = tags;
        //printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            // if cache block is valid and tag matches then we have a hit
            if (cache8srrip[setNum].c[j].valid == 1 && cache8srrip[setNum].c[j].tag == tag)
            {
                //printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                for(long long int k=0; k < no_cache_sets; ++k)
                {
                    //printf("DEBUG: k = %lld Inside LOOP1 the updating cache rrpv values\n", k);
                    for(long long int l=0; l < numOfWays; ++l)
                    {
                        if(cache8srrip[k].c[l].rrpv < 3)
                        cache8srrip[k].c[l].rrpv++;
                        //printf("DEBUG: l = %lld Inside LOOP2 the updating cache rrpv values\n", l);
                    }
                }
                cache8srrip[setNum].c[i].rrpv = 0;
                return 1;
            }

            //Beginning with all misses - that is when the cache is being warmed up.
            else if (cache8srrip[setNum].c[j].valid == 0)
            {
                //printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                cache8srrip[setNum].c[j].valid = 1;
                cache8srrip[setNum].c[j].tag = tag;
                cache8srrip[setNum].c[j].rrpv = MAX_RRPV;
                //printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                return 0;
            }

            //Cache miss at set and cache line is valid
            else
            {
                //printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                count++;
            }

            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                //printf("All cache lines in the set checked and no match so replacement will be performed\n");
                cache8srrip[setNum].c[cache2srrip[setNum].back].tag = tag;
                cache8srrip[setNum].c[cache2srrip[setNum].back].valid = 1;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache8srrip[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache8srrip[setNum].c[i].tag = tag;
                            cache8srrip[setNum].c[p].rrpv = 2;
                            return 0;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache8srrip[k].c[l].rrpv < 3)
                                    cache8srrip[k].c[l].rrpv++;
                            }
                        }
                    }
                }
            }
        }
    //printf("Hit %d Miss %d", hit, miss);
    return 0;
}


int calcforCacheset16srrip(long long indices, long long tags, int size, int numOfWays, int blocksize)
{
    int cache_size = 32*1024, no_cache_blocks = cache_size/blocksize;
    int i, j, count, no_cache_sets = no_cache_blocks/numOfWays;
    long long setNum,tag;

    if(initializeCacheSetSRRIP == 0)
    {
        // initialize maxRRPV i.e. to distant value 3
        for(int i=0; i < no_cache_sets; ++i)
        {
            for(int j=0; j < numOfWays; ++j)
            {
                cache16srrip[i].c[j].rrpv = MAX_RRPV;
            }
        }
        printf("Cache RRPV Initialization done\n");
        initializeCacheSetSRRIP = 1;
    }
    
    // now check for every reference to the cache
        setNum = indices;
        tag = tags;
        //printf("Tag %lld setNum %lld\n", tag, setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            // if cache block is valid and tag matches then we have a hit
            if (cache16srrip[setNum].c[j].valid == 1 && cache16srrip[setNum].c[j].tag == tag)
            {
                //printf("Cache hit at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                for(long long int k=0; k < no_cache_sets; ++k)
                {
                    //printf("DEBUG: k = %lld Inside LOOP1 the updating cache rrpv values\n", k);
                    for(long long int l=0; l < numOfWays; ++l)
                    {
                        if(cache16srrip[k].c[l].rrpv < 3)
                        cache16srrip[k].c[l].rrpv++;
                        //printf("DEBUG: l = %lld Inside LOOP2 the updating cache rrpv values\n", l);
                    }
                }
                cache16srrip[setNum].c[i].rrpv = 0;
                return 1;
            }

            //Beginning with all misses - that is when the cache is being warmed up.
            else if (cache16srrip[setNum].c[j].valid == 0)
            {
                //printf("Cache miss with no data at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                cache16srrip[setNum].c[j].valid = 1;
                cache16srrip[setNum].c[j].tag = tag;
                cache16srrip[setNum].c[j].rrpv = MAX_RRPV;
                //printf("Data added at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                return 0;
            }

            //Cache miss at set and cache line is valid
            else
            {
                //printf("Cache miss at set %lld and cache line %d valid:%d Tag:%ld\n", setNum, j, cache2srrip[setNum].c[j].valid, cache2srrip[setNum].c[j].tag);
                count++;
            }

            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }

            if (count == numOfWays)
            {
                //printf("All cache lines in the set checked and no match so replacement will be performed\n");
                cache16srrip[setNum].c[cache2srrip[setNum].back].tag = tag;
                cache16srrip[setNum].c[cache2srrip[setNum].back].valid = 1;

                // now search for a block in the set with maxRRPV value
                while(1)
                {
                    int found = 0;
                    for(int p = 0; p < numOfWays; ++p)
                    {
                        if(cache16srrip[setNum].c[p].rrpv == 3)
                        {
                            // Replace this cache block (cache block with rrpv value 3) with the incoming block
                            // and give it and rrpv value of 2.
                            found = 1;
                            cache16srrip[setNum].c[i].tag = tag;
                            cache16srrip[setNum].c[p].rrpv = 2;
                            return 0;
                        }
                    }

                    if(found == 0)
                    {
                        for(int k=0; k < no_cache_sets; ++k)
                        {
                            for(int l=0; l < numOfWays; ++l)
                            {
                                if(cache16srrip[k].c[l].rrpv < 3)
                                    cache16srrip[k].c[l].rrpv++;
                            }
                        }
                    }
                }
            }
        }
    //printf("Hit %d Miss %d", hit, miss);
    return 0;
}


int srrip(long long indices, long long tags, int size, int numOfWays, int blocksize)
{
    int answer;

    if (numOfWays == 2)
    {
        answer = calcforCacheset2srrip(indices, tags, size, numOfWays, blocksize);
    }
    else if (numOfWays == 4)
    {
        answer = calcforCacheset4srrip(indices, tags, size, numOfWays, blocksize);
    }
    else if (numOfWays == 8)
    {
        answer = calcforCacheset8srrip(indices, tags, size, numOfWays, blocksize);
    }
    else
    {
        answer = calcforCacheset16srrip(indices, tags, size, numOfWays, blocksize);
    }
    return answer;
}
