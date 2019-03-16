#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct cacheLine
{
    int valid;
    long tag;
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
float calcforCacheset2(int *indices, long *tags, int size, int numOfWays)
{
    int i, j, setNum, count;
    long tag;
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        // printf("Tag %d setNum %d\n",tag,setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache2[setNum].c[j].valid == 1 && cache2[setNum].c[j].tag == tag)
            {
                // printf("Cache hit at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                hit++;
                break;
            }
            //Beginning with all misses
            else if (cache2[setNum].c[j].valid == 0)
            {
                // printf("Cache miss with no data at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                cache2[setNum].c[j].valid = 1;
                cache2[setNum].c[j].tag = tag;
                cache2[setNum].front = (cache2[setNum].front + 1) % numOfWays;
                // printf("Data added at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                miss++;
                break;
            }
            else
            {
                // printf("Cache miss at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                count++;
            }
            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }
            if (count == numOfWays)
            {
                // printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache2[setNum].back);
                miss++;
                cache2[setNum].c[cache2[setNum].back].tag = tag;
                cache2[setNum].c[cache2[setNum].back].valid = 1;
                cache2[setNum].back = (cache2[setNum].back + 1) % numOfWays;
            }
        }
    }
    return ((float)hit / size);
    // printf("Hit %d Miss %d", hit, miss);
}

float calcforCacheset4(int *indices, long *tags, int size, int numOfWays)
{
    int i, j, setNum, count;
    long tag;
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        // printf("Tag %d setNum %d\n",tag,setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache4[setNum].c[j].valid == 1 && cache4[setNum].c[j].tag == tag)
            {
                // printf("Cache hit at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                hit++;
                break;
            }
            //Beginning with all misses
            else if (cache4[setNum].c[j].valid == 0)
            {
                // printf("Cache miss with no data at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                cache4[setNum].c[j].valid = 1;
                cache4[setNum].c[j].tag = tag;
                cache4[setNum].front = (cache4[setNum].front + 1) % numOfWays;
                // printf("Data added at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                miss++;
                break;
            }
            else
            {
                // printf("Cache miss at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache4[setNum].c[j].valid, cache4[setNum].c[j].tag);
                count++;
            }
            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }
            if (count == numOfWays)
            {
                // printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache2[setNum].back);
                miss++;
                cache4[setNum].c[cache4[setNum].back].tag = tag;
                cache4[setNum].c[cache4[setNum].back].valid = 1;
                cache4[setNum].back = (cache4[setNum].back + 1) % numOfWays;
            }
        }
    }
    return ((float)hit / size);
    // printf("Hit %d Miss %d", hit, miss);
}
float calcforCacheset8(int *indices, long *tags, int size, int numOfWays)
{
    int i, j, setNum, count;
    long tag;
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        // printf("Tag %d setNum %d\n",tag,setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache8[setNum].c[j].valid == 1 && cache8[setNum].c[j].tag == tag)
            {
                // printf("Cache hit at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                hit++;
                break;
            }
            //Beginning with all misses
            else if (cache8[setNum].c[j].valid == 0)
            {
                // printf("Cache miss with no data at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                cache8[setNum].c[j].valid = 1;
                cache8[setNum].c[j].tag = tag;
                cache8[setNum].front = (cache8[setNum].front + 1) % numOfWays;
                // printf("Data added at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                miss++;
                break;
            }
            else
            {
                // printf("Cache miss at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache8[setNum].c[j].valid, cache8[setNum].c[j].tag);
                count++;
            }
            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }
            if (count == numOfWays)
            {
                // printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache2[setNum].back);
                miss++;
                cache8[setNum].c[cache8[setNum].back].tag = tag;
                cache8[setNum].c[cache8[setNum].back].valid = 1;
                cache8[setNum].back = (cache8[setNum].back + 1) % numOfWays;
            }
        }
    }
    return ((float)hit / size);
    // printf("Hit %d Miss %d", hit, miss);
}
float calcforCacheset16(int *indices, long *tags, int size, int numOfWays)
{
    int i, j, setNum, count;
    long tag;
    for (i = 0; i < size; i++)
    {
        setNum = indices[i];
        tag = tags[i];
        // printf("Tag %d setNum %d\n",tag,setNum);
        for (j = 0, count = 0; j < numOfWays; j++)
        {
            if (cache16[setNum].c[j].valid == 1 && cache16[setNum].c[j].tag == tag)
            {
                // printf("Cache hit at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                hit++;
                break;
            }
            //Beginning with all misses
            else if (cache16[setNum].c[j].valid == 0)
            {
                // printf("Cache miss with no data at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache2[setNum].c[j].valid, cache2[setNum].c[j].tag);
                cache16[setNum].c[j].valid = 1;
                cache16[setNum].c[j].tag = tag;
                cache16[setNum].front = (cache16[setNum].front + 1) % numOfWays;
                // printf("Data added at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                miss++;
                break;
            }
            else
            {
                // printf("Cache miss at set %d and cache line %d valid:%d Tag:%d\n", setNum, j, cache16[setNum].c[j].valid, cache16[setNum].c[j].tag);
                count++;
            }
            // if (cache2[i].c[j].valid == 0 || cache2[i].c[j].tag!=tag)
            // {
            //     count++;
            // }
            if (count == numOfWays)
            {
                // printf("All cache lines in the set checked and non match so fifo performed back%d\n", cache16[setNum].back);
                miss++;
                cache16[setNum].c[cache16[setNum].back].tag = tag;
                cache16[setNum].c[cache16[setNum].back].valid = 1;
                cache16[setNum].back = (cache16[setNum].back + 1) % numOfWays;
            }
        }
    }
    // printf("Hit %d Miss %d", hit, miss);
    return ((float)hit / size);
}
float fifo(int *indices, long *tags, int size, int numOfWays)
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
