#include<stdio.h>
#include<string.h>
int subs(char* s1,char* s2)
{
int flag,j,i,lim;
lim=strlen(s1)-strlen(s2);
if(lim<0)
flag=0;
else
{
flag=1;
for(i=0;i<=lim;i++)
{
for(j=0;j<strlen(s2);j++)
{
if(*(s1+i+j)==*(s2+j))
flag=1;
else
{flag=0;
break;
}

}
if(flag)
break;
}



}

return flag;
}

int main()
{
char str1[100],str2[100];
puts("\nEnter string 1:\n");
scanf("%[^\n]",str1);
puts("\nEntered string:\n");
puts(str1);
getchar();
puts("\nEnter string 2:\n");
scanf("%[^\n]",str2);
puts("\nEntered string:\n");
puts(str2);
if(subs(str1,str2))
puts("Substring.");
else
puts("Not a substring.");
return 0;
}
