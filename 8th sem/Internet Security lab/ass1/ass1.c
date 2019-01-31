#include <stdio.h>

//Algorithm of extended GCD
// ax+by = gcd(a,b)
int ExtendedGCD(int a, int b, int *x, int *y) 
{ 
    if (b == 0)
    {
    	//Since 'b' = 0, 'a' = gcd, then [ (1*a + 0*b) = gcd ]
    	*x = 1;
    	*y = 0;
    	//printf("\na=%d, b=%d, x=%d, y=%d",a,b,*x,*y);
        return a; //return 'a' as gcd
    }
    
    int currGCD, prev_x,prev_y;
    currGCD = ExtendedGCD(b, a % b, &prev_x, &prev_y);
    
    *x = prev_y;
    *y = prev_x - (a/b)*prev_y;
    //printf("\na=%d, b=%d, x=%d, y=%d",a,b,*x,*y);
    return currGCD;  
      
}

int normalizeInverse(int x,int n)
{
	if(x>0)
		return x%n;
	else
		return normalizeInverse(n+x,n);
}

int main()
{
	int b,n,g, x,y;
	printf("Enter the number to find inverse: ");
	scanf("%d",&b);
	printf("Enter the base of Zn: ");
	scanf("%d",&n);
	printf(">> Finding Multiplicative inverse of %d in z(%d)\n",b,n);
	g = ExtendedGCD(b,n,&x,&y);
	if(g==1)
		printf(">> Proceeding to find inverse [gcd is 1]\n");
	else
	{
		printf(">> Cannot proceed[gcd is %d]. Inverse does not exist!\n",g);
		return 0;
	}
	
	printf(">> The inverse is: %d\n",normalizeInverse(x,n));
	return 0;
}
