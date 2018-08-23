//binary search
//algorithm lab

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define maxstr 10
#define minArrlen 1000
#define maxArrlen 100000000
#define searchkey -5
#define numofShuffles 1000000
#define shifter 3
struct tuple
{
	long long int key;
	char name[maxstr];
	int age;
};

long long int randNum(long int minNum, long int maxNum)
{
	return (minNum + (rand()%(maxNum-minNum)));
}

void Arrshuffler(struct tuple* arr,long long int arrlen)
{
	long long int source, dest;
	struct tuple temp;
	source = randNum(0, arrlen-1);
	dest = randNum(0, arrlen-1);
	
	if(source==dest)
		return;
		
	temp.key = arr[source].key;
	strcpy(temp.name , arr[source].name);
	temp.age = arr[source].age;
	
	arr[source].key = arr[dest].key;
	strcpy(arr[source].name, arr[dest].name);
	arr[source].age = arr[dest].age;
	
	arr[dest].key = temp.key;
	strcpy(arr[dest].name, temp.name);
	arr[dest].age = temp.age;
}

void createRandString(char *str, int len)
{
	int i;
	for(i=0;i<len-1;i++)
	{
		str[i] = (char)randNum('A', 'Z');
	}
	
	str[len-1]='\0';
}

struct tuple* generateRandArr(long int arrlen)
{
	struct tuple *arr;
	long long int i;
	arr = (struct tuple*)malloc((arrlen+1)*sizeof(struct tuple));
	
	//generate linear sorted array
	for(i=0;i<arrlen;i++)
	{
		arr[i].key = i+1;
		createRandString(arr[i].name, maxstr);
		arr[i].age = (int)randNum(1, 99);
	}
	
	/*
	//shuffle the array a particular number of times
	for(i=0;i<numofShuffles;i++)
	{
		Arrshuffler(arr,arrlen);
	}
	*/
	return arr;
}

void printTuple(struct tuple t)
{
	printf("%lld\t%s\t%d\n",t.key,t.name,t.age);
}

void printArr(struct tuple *arr, long int arrlen)
{
	long long int i;
	for(i=0;i<arrlen;i++)
		printTuple(arr[i]);
}

void SeqSearch(struct tuple *arr, long long int arrlen, long long int skey)
{
	long long int i;
	for(i=0;i<arrlen;i++)
	{
		if(arr[i].key==skey)
		{
			//printTuple(arr[i]);
			return;
		}
	}
	//printf("Not Found!\n");
}

void SeqSearchOpt(struct tuple *arr, long long int arrlen, long int skey)
{
	//this is optimized
	long long int i=0;
	arr[arrlen].key=skey;
	while(1)
	{
		if(arr[i].key==skey)
			break;
		i++;
	}
	if(i<arrlen)
	{
		//printTuple(arr[i]);
		return;
	}
	else
	{
		//printf("Not Found!\n");
		return;
	}
}

void BinSearch(struct tuple *arr, long long int arrlen, long int skey)
{
	long long int i,u,l;
	l=1;
	u=arrlen;
	while(u>=l)
	{
		i=(u+l)/2;
		if(skey==arr[i-1].key)
		{
			//printTuple(arr[i]);
			return;
		}
		else if(skey<arr[i-1].key)
		{
			u=i-1;
		}
		else
		{
			l=i+1;
		}
	}
	//printf("Not Found!\n");
}
long long int calcTimeToSearch(struct tuple *arr, long long int arrlen, long int skey)
{
	struct timespec start, stop;
	long long int time_taken;
	clock_gettime(CLOCK_MONOTONIC, &start);
	// 
	BinSearch(arr, arrlen, searchkey);
	clock_gettime(CLOCK_MONOTONIC , &stop);
	time_taken = (( stop.tv_sec - start.tv_sec )*1000000000) + ( stop.tv_nsec - start.tv_nsec );
	return time_taken;
}

int main()
{
	srand(time(NULL));
	long long int key, arrlen, val;
	struct tuple *arr;
	arr = generateRandArr(maxArrlen);
	for(arrlen=minArrlen; arrlen<=maxArrlen; arrlen*=shifter)
	{
		
		//printArr(arr, arrlen);
		printf("%lld %lld\n",arrlen,calcTimeToSearch(arr, arrlen, searchkey));
		
	}
	
	free(arr);

	return 0;
}
