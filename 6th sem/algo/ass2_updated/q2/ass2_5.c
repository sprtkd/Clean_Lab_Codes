//sorting algorithms
//algorithm lab

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define maxstr 10
#define minArrlen 1000
#define maxArrlen 1000000
#define arrShifter 50000
#define numofShuffles 10000
#define seed_val 33

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
	source = randNum(1, arrlen-1);
	dest = randNum(1, arrlen-1);
	
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

struct tuple* generateRandomArr(long int arrlen)
{
	struct tuple *arr;
	long int i,j;
	arr = (struct tuple*)malloc(arrlen*sizeof(struct tuple));
	
	//generate linear reversed sorted array
	for(i=1,j=arrlen-1;i<arrlen;i++,j--)
	{
		arr[i].key = j;
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

//1-dest, 2-source
void copy(struct tuple *arrloc1, struct tuple *arrloc2)
{
	arrloc1->key = arrloc2->key;
	strcpy(arrloc1->name,arrloc2->name);
	arrloc1->age = arrloc2->age;
}

void HeapSort(struct tuple *arr, long int arrlen)
{
	long int i,j,l,r;
	
	struct tuple R;
	H1:
		l= (int)(arrlen/2);
		r=arrlen-1;
	H2:
		if(l>0)
		{
			l=l-1;
			copy(&R,&(arr[l]));
		}
		else
		{
			copy(&R,&(arr[r]));
			copy(&(arr[r]),&(arr[0]));
			r=r-1;
			
			if(r==0)
			{
				copy(&(arr[0]),&R);
				goto H9;
			}
		}
		
	H3:
		j=l;
		
	H4:
		i=j;
		j=2*j+1;
		
		if(j<r)
			goto H5;
		if(j==r)
			goto H6;
		if(j>r)
			goto H8;
			
	H5:
		if(arr[j].key < arr[j+1].key)
			j=j+1;
		
	H6:
		if(R.key >= arr[j].key)
			goto H8;
			
	H7:	
		copy(&(arr[i]),&(arr[j]));
		goto H4;
		
	H8:
		copy(&(arr[i]),&R);
		goto H2;
			
	H9:
		return;
	
}


double calcTimeToSort(struct tuple *arr, long int arrlen)
{
	clock_t t;
	double time_taken;
	t = clock();
	HeapSort(arr, arrlen);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	return time_taken;
}

int main()
{
	srand(seed_val);
	long int key, arrlen, val;
	struct tuple *arr;

	for(arrlen=minArrlen; arrlen<=maxArrlen; arrlen+=arrShifter)
	{
		arr = generateRandomArr(arrlen+1);
		//printArr(arr, arrlen+1);
		printf("%ld %f\n",arrlen,calcTimeToSort(arr, arrlen+1));
		//printArr(arr, arrlen+1);
		free(arr);
	}

	return 0;
}
