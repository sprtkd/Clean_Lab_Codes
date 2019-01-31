#include <stdio.h>
//Linear congruential generator

#define X0 2
#define mul 2
#define c 1



int lcgRand(int a, int b, int *xn)
{
	int m, new;
	m = b - a + 1;
	
	if(X0 > m || mul > m || c > m)
	{
		printf("\nCannot compute!!");
		return 0;
	}

	new = ( mul * (*xn) + c) % m;
	
	*xn = new;

	return (new + a);	

}




int main()
{
	
	int A, B, N, i;
	int Xn = X0;	

	printf("\nEnter A(the starting value),\nB(the ending value),\nN(the number of values to print):\n");

	scanf("%d %d %d", &A, &B, &N);
	
	printf("\nThe random nos.:\n");
	for( i = 1; i <= N; i++ )
 	{
		printf("\n%d", lcgRand(A, B, &Xn));		
	}

	return 0;
}
