#include<stdio.h>

int reverseIntger(int n)
{
int reverse=0;
 while (n != 0)
   {
      reverse = reverse * 10;
      reverse = reverse + n%10;
      n       = n/10;
   }

return reverse;
}

int main()
{
int num;
printf("\nEnter an integer:");
scanf("%d",&num);

printf("\nThe reverse of no. is:%d.",reverseIntger(num));
return 0;
}

