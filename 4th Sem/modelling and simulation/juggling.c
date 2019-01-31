#include <stdio.h>

#define MAX 100

void printArray(int *arr, int n)
{
	int i;
	printf("\nList:\n");
	for( i = 0; i < n; i++ )
	{
		printf("\n%d", arr[i]);	
	}
	 
	
}

void juggling(int *arr, int n)
{
	if( n==0 || n==1)
		return;
	
	int val, i;
	val = arr[n-1];
	
	for( i = n-1; i >= 0; i-- )
	{
		arr[i+1] = arr[i];
	}

	arr[0] = val;
	
}

int main()
{
	int n, arr[MAX], i, opt;

	printf("\nEnter the number of things you want to juggle:");
	scanf("%d", &n);
	
	printf("\nEnter the numbers:\n");
	
	for( i = 0; i < n; i++ )
	{
		scanf("%d", &arr[i]);	
	}
	
	while(1)
	{
		printArray(arr, n);
	
		juggling(arr, n);
		
		printf("\npress any key to continue or x to end...");
		
		if(getchar()=='x')
			break;
	}
	
	return 0;
}
