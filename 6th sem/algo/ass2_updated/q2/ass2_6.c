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

void QuickSort(struct tuple *arr, long int arrlen)
{
	long m,top, *stack0, *stack1,n=arrlen,l,r,i,j,rn;
	stack0 = (long*)malloc(maxArrlen*sizeof(long));
	stack1 = (long*)malloc(maxArrlen*sizeof(long));
	struct tuple temp1,temp2;
	
	
	step0:  
		m=1;
		
	step1:  
		if(n<=m)
			goto step9;
		else
		{
			top=-1;
			l=0;
			r=n-1;
		}
		
	step2:
		i=l;
		j=r+1;
		copy(&temp1,&arr[rn%(r+1-l) + l]);
		copy(&arr[rn%(r+1-l) + l],&arr[l]);
		copy(&arr[l],&temp1);
			
		
	step3:  
		i=i+1;
		if(arr[i].key<temp1.key && i<j)
			goto step3;
	
	step4:  
		j=j-1;
		if(temp1.key<arr[j].key && j>i-1)
			goto step4;
	
	step5:  
		if(j<=i)
		{
			copy(&temp2,&arr[l]);
			copy(&arr[l],&arr[j]);
			copy(&arr[j],&temp2);
			goto step7;
		}
		
	step6:  
		copy(&temp2,&arr[i]);
		copy(&arr[i],&arr[j]);
		copy(&arr[j],&temp2);
		goto step3;
		
	step7:  
		if(r-j>=j-l && j-l>m)
		{
			top++;
			stack0[top]=j+1;
			stack1[top]=r;
			r=j-1;
			goto step2;
		}
		
		if(j-l>r-j && r-j>m)
		{
			top++;
			stack0[top]=l;
			stack1[top]=j-1;
			l=j+1;
			goto step2;
		}
		
		if(j-l<=m && m<r-j)
		{
			l=j+1;
			goto step2;
		}
		
		if(j-l>m && m>=r-j)
		{
			r=j-1;
			goto step2;
		}
			
	step8:  
		if(top>=0)
		{
			l=stack0[top];
			r=stack1[top];
			top--;
			goto step2;
		}
	
	step9: return;
}


double calcTimeToSort(struct tuple *arr, long int arrlen)
{
	clock_t t;
	double time_taken;
	t = clock();
	QuickSort(arr, arrlen);
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
