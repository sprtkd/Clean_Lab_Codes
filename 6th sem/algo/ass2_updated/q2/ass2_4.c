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

struct tuple* generateRandomArr(long int arrlen)
{
	struct tuple *arr;
	long int i,j;
	arr = (struct tuple*)malloc(2*arrlen*sizeof(struct tuple));
	
	//generate linear reversed sorted array
	for(i=0,j=arrlen-1;i<arrlen;i++,j--)
	{
		arr[i].key = j+1;
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

void MergeSort(struct tuple *arr, long int arrlen)
{
	long i,j,k,l,s,d,f,temp;
	N1:
		s=0;
	
	N2:
		if(s==0)
		{
			i=0;
			j=arrlen-1;
			k=arrlen;
			l=(2*arrlen)-1;
		}
		else
		{
			i=arrlen;
			j=(2*arrlen)-1;
			k=0;
			l=arrlen-1;
		
		}
		d=1;
		f=1;
	
	N3:
		if(arr[i].key > arr[j].key)
			goto N8;
		if(i==j)
		{
			copy(&(arr[k]),&(arr[i]));
			goto N13;
		}
		
	N4:
		copy(&(arr[k]),&(arr[i]));
		k=k+d;
	
	N5:
		i=i+1;
		if(arr[i-1].key <= arr[i].key)
			goto N3;
	
	N6:
		copy(&(arr[k]), &(arr[j]));
		k=k+d;
		
	N7:
		j=j-1;
		if(arr[j+1].key <= arr[j].key)
			goto N6;
		else
			goto N12;
			
	N8:
		copy(&(arr[k]), &(arr[j]));
		k=k+d;
	
	N9:
		j=j-1;
		if(arr[j+1].key <= arr[j].key)
			goto N3;
	
	N10:
		copy(&(arr[k]),&(arr[i]));
		k=k+d;
		
	N11:
		i=i+1;
		if(arr[i-1].key <= arr[i].key)
			goto N10;
			
	N12:
		f=0;
		d=-d;
		
		temp=k;
		k=l;
		l=temp;
		
		goto N3;
		
	N13:
		if(f==0)
		{
			s=1-s;
			goto N2;
		}
		else
		{
			//sorting complete
			if(s==0)
			{
				for(i=0;i<arrlen;i++)
					copy(&(arr[arrlen+i]),&(arr[i]));
			}
		}		
	
}


double calcTimeToSort(struct tuple *arr, long int arrlen)
{
	clock_t t;
	double time_taken;
	t = clock();
	MergeSort(arr, arrlen);
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
		arr = generateRandomArr(arrlen);
		//printArr(arr, arrlen);
		printf("%ld %f\n",arrlen,calcTimeToSort(arr, arrlen));
		//printArr(arr, arrlen);
		free(arr);
	}
	
	

	return 0;
}
