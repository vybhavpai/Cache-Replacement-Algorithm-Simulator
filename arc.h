#include <bits/stdc++.h>
using namespace std;


long int tagValue[1000000];
long int setValue[1000000];


class AdaptiveReplacement {
    int c; // cache block size
    int p;
    deque <long long> T1, T2, B1, B2;
    set <long long> cache;

public:

    static int hit;
    static int miss;

    AdaptiveReplacement() {

    }

    AdaptiveReplacement(int number_of_ways){
        c=number_of_ways;
        p = 0;
    }

    void replace(long long x) {
        long long old;
        if (T1.size()>=1 && ((find(B2.begin(),B2.end(),x)!=B2.end() && T1.size()==p) || T1.size()>p )) {
            old = T1.front();
            T1.pop_front();
            B1.push_back(old);
        }
        else {
            old = T2.front();
            T2.pop_front();
            B2.push_back(old);
            }
        cache.erase(old);
    }

    void re(long long x) {

        if (find(T1.begin(),T1.end(),x)!=T1.end() || find(T2.begin(),T2.end(),x)!=T2.end())
        {
            hit++;
            if(find(T1.begin(),T1.end(),x)!=T1.end())
            {
                auto it = find(T1.begin(),T1.end(),x);
                T1.erase(it);
            } else{
                auto it = find(T2.begin(),T2.end(),x);
                T2.erase(it);
            }
            T2.push_back(x);
        }

        else if (find(B1.begin(),B1.end(),x)!=B1.end()) {
            miss++;
            p = min(c, p+1);
            replace(x);
            auto it = find(B1.begin(),B1.end(),x);
            B1.erase(it);
            T2.push_back(x);
            cache.insert(x);
        }

        else if (find(B2.begin(),B2.end(),x)!=B2.end()) {
            miss++;
            p = max(0, p-1);
            replace(x);
            auto it = find(B2.begin(),B2.end(),x);
            B2.erase(it);
            T2.push_back(x);
            cache.insert(x);
        }
        else {
            miss++;
            if (T1.size()+B1.size() == c) {
                if(T1.size()<c) {
                    B1.pop_front();
                    replace(x);
                }
                else {
                    long long old = T1.front();
                    T1.pop_front();
                    cache.erase(old);
                }
            }

            else if(T1.size()+B1.size()< c && T1.size()+T2.size()+B1.size()+B2.size()>=c){
                if (T1.size()+T2.size()+B1.size()+B2.size() == 2*c) {
                    B2.pop_front();
                }
                replace(x);
            }
            T1.push_back(x);
            cache.insert(x);
        }

        // cout<<"Item: "<<x<<"\n";
        // cout<<"Cache: ";
        // for(auto it = cache.begin(); it!=cache.end(); ++it)
        //     cout<<*it<<" ";
        // cout<<"\np: "<<p;
        // cout<<"\nT1: ";
        // for(auto it = T1.begin(); it!=T1.end(); ++it)
        //     cout<<*it<<" ";
        // cout<<"\nB1: ";
        // for(auto it = B1.begin(); it!=B1.end(); ++it)
        //     cout<<*it<<" ";
        // cout<<"\nT2: ";
        // for(auto it = T2.begin(); it!=T2.end(); ++it)
        //     cout<<*it<<" ";
        // cout<<"\nB2: ";
        // for(auto it = B2.begin(); it!=B2.end(); ++it)
        //     cout<<*it<<" ";
        // cout<<"\n Hits: "<<hit<<"\nMiss: "<<miss<<"\n";
    }

};

int AdaptiveReplacement::hit = 0;
int AdaptiveReplacement::miss = 0;


float ARC(long long int tagValue[], long long int setValue[], long long int size, int numberOfWays) {
    long long size_of_cache = 1024*1024; // 1MB
    int size_of_one_block = 64; // 64 B
    long long no_of_blocks = size_of_cache/size_of_one_block;
    long long no_of_sets = no_of_blocks/numberOfWays;
    AdaptiveReplacement arc[no_of_sets];
    for(int i=0;i<no_of_sets;i++)
        arc[i]= AdaptiveReplacement(numberOfWays);
    for(int i=0;i<size;i++)
        arc[setValue[i]].re(tagValue[i]);
    return (AdaptiveReplacement::hit/(AdaptiveReplacement::hit+AdaptiveReplacement::miss));
}
