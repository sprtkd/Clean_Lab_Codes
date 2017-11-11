#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define maxstride 20
#define maxwordsize 1000000
#define arrsize 100000000

#define wordsizeshifter 100

void run_stride(int *arr,long int s,long int w)
{
	long long int i,j;
	long int timet;
	clock_t start_t, end_t;
	start_t = clock();
	
	for(i=0;i<w;i+=s)
	{
		j=arr[i];
	}
	
	end_t = clock();
	timet = (end_t - start_t);
	printf("%ld %ld %ld\n",s,w,timet);
}

int main()
{
	long int StrideSize,Wordsize;
	int *arr;
	arr = (int*)malloc(arrsize*sizeof(int));
	
	for(StrideSize=1;StrideSize<=maxstride;StrideSize++)
	{
		for(Wordsize=1;Wordsize<=maxwordsize;Wordsize+=wordsizeshifter)
		{
			run_stride(arr,StrideSize,Wordsize);
		}
	}
	
	return 0;
}
