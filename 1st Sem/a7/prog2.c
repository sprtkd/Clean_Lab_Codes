#include<stdio.h>

int Compute_GCD(int a,int b)
{
int n1,n2;
if(a>=b)
{
n1=a;
n2=b;
}
else
{
n1=b;
n2=a;
}
if (n2!=0)
       return Compute_GCD(n2, n1%n2);
    else 
       return n1;
}

int main()
{
int x,y;
printf("\nEnter two integers (x,y):");
scanf("%d,%d",&x,&y);
printf("\nThe gcd of two nos. is:%d",Compute_GCD(x,y));


return 0;
}

