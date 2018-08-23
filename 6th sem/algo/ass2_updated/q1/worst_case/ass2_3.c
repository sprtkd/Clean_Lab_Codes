//sorting algorithms
//algorithm lab

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define maxstr 10
#define minArrlen 1000
#define maxArrlen 100000
#define arrShifter 10000

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

void createRandString(char *str, int len)
{
	int i;
	for(i=0;i<len-1;i++)
	{
		str[i] = (char)randNum('A', 'Z');
	}
	
	str[len-1]='\0';
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

struct tuple* generateReverseArr(long int arrlen)
{
	struct tuple *arr;
	long int i,j;
	arr = (struct tuple*)malloc(arrlen*sizeof(struct tuple));
	
	//generate linear reversed sorted array
	for(i=0,j=arrlen-1;i<arrlen;i++,j--)
	{
		arr[i].key = j+1;
		createRandString(arr[i].name, maxstr);
		arr[i].age = (int)randNum(1, 99);
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

void swap(struct tuple *arrloc1, struct tuple *arrloc2)
{
	struct tuple temp;
	
	temp.key = arrloc1->key;
	strcpy(temp.name,arrloc1->name);
	temp.age = arrloc1->age;
	
	arrloc1->key = arrloc2->key;
	strcpy(arrloc1->name,arrloc2->name);
	arrloc1->age = arrloc2->age;
	
	arrloc2->key = temp.key;
	strcpy(arrloc2->name,temp.name);
	arrloc2->age = temp.age;
	
}

void BubbleSort(struct tuple *arr, long int arrlen)
{
	long int bound=arrlen-1, t, i;
	while(1)
	{
		t=-1;
		for (i = 0; i < bound; i++)
		{
			if((arr[i].key) > (arr[i+1].key))
			{
				swap( &(arr[i]), &(arr[i+1]) );
				t=i;
			}
		}
		if(t==-1)
			break;
		else
			bound = t;
	}
}


double calcTimeToSort(struct tuple *arr, long int arrlen)
{
	clock_t t;
	double time_taken;
	t = clock();
	BubbleSort(arr, arrlen);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	return time_taken;
}

int main()
{
	srand(time(NULL));
	long int key, arrlen, val;
	struct tuple *arr;

	for(arrlen=minArrlen; arrlen<=maxArrlen; arrlen+=arrShifter)
	{
		arr = generateReverseArr(arrlen);
		//printArr(arr, arrlen);
		printf("%ld %f\n",arrlen,calcTimeToSort(arr, arrlen));
		//printArr(arr, arrlen);
		free(arr);
	}
	
	

	return 0;
}
