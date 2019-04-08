



pair<long long int,long long int> cacheLfu[512];

int lfu(long long int tagValue, int setValue ,int numberOfWays)
{
	int i,j,k;
	
	//memset(cacheLfu,-1,sizeof(cacheLfu));
	long long int hits=0;
	k=-1;
	int mi=1e9;
	long long int p= numberOfWays*setValue;
	//cout<<"Hello"<<endl;
	for(j=p;j<p+numberOfWays;j++)
	{
		if(cacheLfu[j].first==tagValue)
		{
			cacheLfu[j].second++;
			return 1;
		}
	}
	if(j==p+numberOfWays)
	{
		for(j=p;j<p+numberOfWays;j++)
		{
			if(cacheLfu[j].second<mi)
			{
				mi=cacheLfu[j].second;
				k=j;
			}
		}
		cacheLfu[k].first=tagValue;
		cacheLfu[k].second=1;
	}
	return 0;

}
