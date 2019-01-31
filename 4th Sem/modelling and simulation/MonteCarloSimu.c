/*Program to find the integral of a function using Monte Carlo Simulation*/

#include<stdio.h>
#include<math.h>
#include<time.h>

void generateStockRandomFnStream(int a, int b, int n, float *arr)
{
	int i, m;
	m = b - a + 1;
	for(i = 0; i < n; i++)
	{
		arr[i] = rand() % m + a;
	}
}


//this is the defined function...
float myDefFunc(float x)
{
	return pow(sin(x),2.0);//(sinx)^2
}

int main()
{
	srand(time(NULL));
	int a,b,n,i;
	float sum, integral;
	printf("Enter start and stop points of integration:");
	scanf("%d %d",&a,&b);
	printf("Enter the number of random points to be generated:");
	scanf("%d",&n);
	float arrRand[n];
	generateStockRandomFnStream(a,b,n,arrRand);
	sum=0.0;
	for(i=1;i<=n;i++)
	{
		sum=sum+myDefFunc(arrRand[i-1]);
	}
	
	integral=(float)((b-a)*sum/n);
	printf("\nThe integral is:%f.",integral);
	return 0;
}
