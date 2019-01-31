#include<stdio.h>

struct complex
{int a;
int b;
};

int main()
{
struct complex cp1,cp2,add,sub,mult;
printf("\nEnter a complex no.(a,b):");
scanf("%d,%d",&cp1.a,&cp1.b);
printf("\nEnter another complex no.(a,b):");
scanf("%d,%d",&cp2.a,&cp2.b);
add.a=cp1.a+cp2.a;
add.b=cp1.b+cp2.b;
sub.a=cp1.a-cp2.a;
sub.b=cp1.b-cp2.b;
mult.a=(cp1.a*cp2.a)-(cp1.b*cp2.b);
mult.b=(cp1.a*cp2.b)+(cp1.b*cp2.a);

printf("\nComplex 1.:%d+%di\nComplex 2.:%d+%di\nSum:%d+%di\nSubtraction:%d+%di\nMultiplication:%d+%di",cp1.a,cp1.b,cp2.a,cp2.b,add.a,add.b,sub.a,sub.b,mult.a,mult.b);
return 0;
}
