#include<stdio.h>
char revstr[100];
char *strptr;


int reversestr(char *str1)
{
if (*str1)
   {
       reversestr(str1+1);
       *strptr=*str1;
	strptr=strptr+1;
	*strptr='\0';
	
   }
return 0;
}

int main()
{
char str[100];
printf("\nEnter a string:");
scanf("%[^\n]",str);
printf("\nYou have entered:\n");
puts(str);
printf("\nThe reversed string is:\n");
strptr=revstr;
reversestr(str);
puts(revstr);
return 0;
}
