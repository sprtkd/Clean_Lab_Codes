#include<stdio.h>
#include<string.h>
int reverse(char* s)
{
int limit,i,n;
char tmp;
n=strlen(s)-1;
limit=strlen(s)/2;
for(i=0;i<limit;i++)
{
tmp=*(s+i);
*(s+i)=*(s+n-i);
*(s+n-i)=tmp;
}

return 0;
}

int main()
{
char str[100];
puts("\nEnter a string:\n");
scanf("%[^\n]",str);
puts("\nEntered string:\n");
puts(str);
puts("\nReversed string is:");
reverse(str);
puts(str);
return 0;
}
