#include<bits/stdc++.h>
// #include "lru.h"
#include "fifo.h"

using namespace std;


long long int tagValue[1000000],setValue[1000000] ;



long long int decimal(string temp){
    long long int sum=0,p=1;
    for(int i=temp.size()-1;i>=0;i--)
    {
        sum+=(temp[i]-'0')*p;
        p*=2;
    }
    return sum;
}
 
 
string sintobin(char temp){
    switch(temp)
    {
        case '0' : return "0000";
                    break;
        case '1' : return "0001";
                    break;
        case '2' : return "0010";
                    break;
        case '3' : return "0011";
                    break;
        case '4' : return "0100";
                    break;
        case '5' : return "0101";
                    break;
        case '6' : return "0110";
                    break;
        case '7' : return "0111";
                    break;
        case '8' : return "1000";
                    break;
        case '9' : return "1001";
                    break;
        case 'a' : return "1010";
                    break;
        case 'b' : return "1011";
                    break;
        case 'c' : return "1100";
                    break;
        case 'd' : return "1101";
                    break;
        case 'e' : return "1110";
                    break;
        case 'f' : return "1111";
                    break;
 
    }
}
 
pair<long long int,long long int> hextodec(string s,int ways)
{
    string binary = "",binequi = "",setno = "",tagno = "";
    char temp;
    int waybits = log2(ways),i;
    long long int set,tag;
    for(i=2;i<14;i++)
    {
        temp = s[i];
        //cout<<temp<<"is temp  ";
        binequi = sintobin(temp);
        //cout<<binequi<<"is binary"<<endl;
        binary += binequi;
    }
    //cout<<binary<<" is binary "<<endl;
    for(i=28+waybits;i<42;i++)
        setno += binary[i];
 
    for(i=0;i<28+waybits;i++)
        tagno += binary[i];
    //cout<<setno<<" "<<tagno<<endl;
    set = decimal(setno);
    tag = decimal(tagno);
    //cout<<set<<"  "<<tag<<endl;
    return {tag,set};
 
}





int stringtoint(string temp)
{
	int ans=0;
	for(int i=0;i<temp.size();i++)
	{
		ans=10*ans+(temp[i]-'0');
	}
	return ans;
}


int main(int argc , char** argv )
{
	int i,numberOfWays;
	string algorithm,filename;
	for(i=1;i<argc;i++)
	{
		if(i==1)algorithm=argv[i];
		else if(i==2) filename=argv[i];
		else if(i==3) numberOfWays=stringtoint(argv[i]);
	}
	fstream file; 
	file.open(filename.c_str());
	int counter=0;
	long long int read=0,write=0,size=0;
	string word;
	
	while (file >> word) 
    { 
    	if(counter==1)
    	{
    		if(word=="R")read++;
    		else write++;
    	}
    	else if(counter==2)
    	{
    		pair<long long int,long long int> p=hextodec(word,numberOfWays);
    		tagValue[size]=p.first;
    		setValue[size]=p.second;
    		size++;
    	}
    	counter=(counter+1)%3;	    
    } 
	
	//cout<<algorithm<<" "<<filename<<endl;
	//cout<<read<<" "<<write<<" "<<size<<endl;
	
	transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);
	if(algorithm=="srrip")
	{
		//py
	}
	else if(algorithm=="rrp")
	{
		//ankit
	}
	else if(algorithm=="nru")
	{
		//vybhav
	}
	else if(algorithm=="lfu")
	{
		//arqum
	}
	else if(algorithm=="lru")
	{
		//shrinidhi
        // arguments to lru function: tagValue[size], setValue[size], size, numberOfWays
        // Giving error check it 
        //  float hitratio = (lru(tagValue,setValue,size,numberOfWays))*100; 
	}
	else if(algorithm=="plru")
	{
		//chaitanya
	}
	else if(algorithm=="fifo")
	{
		float hitratio = fifo(tagValue,setValue,size,numberOfWays)*100;
	}
	return 0;
}


