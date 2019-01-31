#include<stdio.h>

int stringLength(char src[])
{
int i,charcount=0;
for(i=0;src[i]!='\0';i++)
{
if(src[i]==' ')
continue;
charcount++;

}

return charcount;
}

int main()
{
char str[100];
printf("\nEnter a string:");
scanf("%[^\n]",str);
printf("\nYou have entered:\n");
puts(str);
printf("\nThe no. of characters entered in the string is:%d.",stringLength(str));
return 0;
}
