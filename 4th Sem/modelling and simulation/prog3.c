//blum blum shub generator..
#include <stdio.h>
#define P 47
#define Q 67
#define R 207
#define maxlen 100


int gcd(int a, int b)
{
	// Everything divides 0 
    if (a == 0 || b == 0)
       return 0;

    // base case
    if (a == b)
        return a;

    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}



int main()
{
	int N, X, A, B, iter, stream[maxlen], i, M;
	
	N = P*Q;
	
	if((P%4!=3)||(Q%4!=3)||(gcd(N, R) != 1))
	{
		printf("\nBBS cannot be generated!!");
		return 0;
	}
	
	N = P*Q;
	X = (R*R)%N; //seeding
	
	printf("\nEnter A(the starting value),\nB(the ending value),\nand the number of values to print:\n");

	scanf("%d %d %d", &A, &B, &iter);
	
	M = B- A +1;
	
	for(i = 0; i < iter; i++)
	{
		X = (X*X) % N;
	    stream[i] = X % M;
		
	}
	
	printf("\n");
	
	for(i = 0; i < iter; i++)
	{
		printf("\n%d", stream[i] + A);
		
	}
	
	
	return 0;
}
