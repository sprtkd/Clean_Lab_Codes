//sequential search
//algorithm lab

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define maxstr 10
#define minArrlen 10000
#define maxArrlen 1000000
#define searchkey 100000009
#define numofShuffles 1000000

struct tuple
{
	long int key;
	char name[maxstr];
	int age;
};

long int randNum(long int minNum, long int maxNum)
{
	return (minNum + (rand()%(maxNum-minNum)));
}

void Arrshuffler(struct tuple* arr,long int arrlen)
{
	long int source, dest;
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
	long int i;
	arr = (struct tuple*)malloc(arrlen*sizeof(struct tuple));
	
	//generate linear sorted array
	for(i=0;i<arrlen;i++)
	{
		arr[i].key = i+1;
		createRandString(arr[i].name, maxstr);
		arr[i].age = (int)randNum(1, 99);
	}
	
	//shuffle the array a particular number of times
	for(i=0;i<numofShuffles;i++)
	{
		Arrshuffler(arr,arrlen);
	}
	
	return arr;
}

void printTuple(struct tuple t)
{
	printf("%ld\t%s\t%d\n",t.key,t.name,t.age);
}

void printArr(struct tuple *arr, long int arrlen)
{
	long int i;
	for(i=0;i<arrlen;i++)
		printTuple(arr[i]);
}

void SeqSearch(struct tuple *arr, long int arrlen, long int skey)
{
	long int i;
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

double calcTimeToSearch(struct tuple *arr, long int arrlen, long int skey)
{
	clock_t t;
	double time_taken;
    t = clock();
    SeqSearch(arr, arrlen, searchkey);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	return time_taken;
}

int main()
{
	srand(time(NULL));
	long int key, arrlen, val;
	struct tuple *arr;

	for(arrlen=minArrlen; arrlen<=maxArrlen; arrlen+=100000)
	{
		arr = generateRandArr(arrlen);
		//printArr(arr, arrlen);
		printf("%ld %f\n",arrlen,calcTimeToSearch(arr, arrlen, searchkey));
		free(arr);
	}
	
	

	return 0;
}
