#include<stdio.h>

int basechange(int a,int b)
{
int arr[100],i;
int dividend,quotient,sum;

if(b==1)
{puts("\nBase cannot be one!");
return 0;
}
quotient=a;
for(i=0;quotient!=0;i++)
{
dividend=quotient;
quotient=dividend/b;
arr[i]=dividend%b;


}
sum=0;
i--;
while(i+1)
{
sum=(sum*10)+arr[i];
i--;

}




return sum;
}

int main()
{
int x,n;
printf("\nEnter a number:");
scanf("%d",&x);
printf("\nEnter the base to which you want to change:");
scanf("%d",&n);
printf("\nNumber in decimal:%d\nConverted to base of %d: %d\n",x,n,basechange(x,n));
return 0;
}
