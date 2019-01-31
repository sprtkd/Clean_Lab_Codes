#include<stdio.h>

float powernum(float x,int n)
{
float res=1;;
if(n>=0)
{
while(n--)
res=res*x;
}
else
{while(n++)
res=res/x;
}
return res;
}

int swapnum(int *num1,int *num2)
{
int temp;
temp=*num1;
*num1=*num2;
*num2=temp;
return 0;
}

int gcdnum(int x,int y)
{
int dividend,divisor,rem;
rem=1;
if(x==0||y==0)
return 0;
if(x>=y)
{
dividend=x;
divisor=y;
}
else
{
dividend=y;
divisor=x;
}

while(rem)
{
rem=dividend%divisor;
if(rem)
{
dividend=divisor;
divisor=rem;
}

}
return divisor;
}

int arrsum(int arr[],int n)
{
int i,sum;
sum=0;
for(i=0;i<n;i++)
{
sum=sum+arr[i];
}
return sum;
}

int remspacestr(char* st,char* stn)
{
while(1)
{
if(*st=='\0')
break;
if(*st!=' ')
{
*stn=*st;
stn++;
}
st++;
}
*stn='\0';
return 0;
}

int main()
{
float x;
int m,i,n,arr[100];
char str[100],strnew[100]="\0";
printf("\nEnter x,n to compute x^n:");
scanf("%f,%d",&x,&n);
printf("\nThe computed power is:%f.",powernum(x,n));

printf("\nEnter x,y for swapping:");
scanf("%d,%d",&m,&n);
swapnum(&m,&n);
printf("\nAfter swapping:%d,%d.",m,n);

printf("\nEnter x,y for computing gcd:");
scanf("%d,%d",&m,&n);
printf("\nGcd is:%d.",gcdnum(m,n));

printf("\nEnter how many elements you want to store in the array:");
scanf("%d",&n);
printf("\nEnter elements of array:");
for(i=0;i<n;i++)
{
printf("\nEnter element %d: ",i+1);
scanf("%d",&arr[i]);
}
printf("\n");
for(i=0;i<n;i++)
{
printf("\nEntered element %d: %d",i+1,arr[i]);
}
printf("\nSum of elements:%d.",arrsum(arr,n));

getchar();

printf("\nEnter a string:\n");
scanf("%[^\n]",str);
printf("\nEntered string is:\n");
puts(str);
remspacestr(str,strnew);
puts("New string without blanks:\n");
puts(strnew);
return 0;
}
