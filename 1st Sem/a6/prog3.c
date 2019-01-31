#include<stdio.h>

int swap(int *a,int *b)
{
int temp;
temp=*a;
*a=*b;
*b=temp;

return 0;
}

int main()
{
int x,y;
printf("\nEnter two numbers(x,y):");
scanf("%d,%d",&x,&y);
printf("\nx:%d\ty:%d",x,y);
puts("\nAfter swapping..");

swap(&x,&y);
printf("\nx:%d\ty:%d\n",x,y);
return 0;
}
