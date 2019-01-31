#include<stdio.h>

int wordrev(char *str1,char *str2)
{
char word[100];
int i=0;
int lettercount=-1;
int snewcount=0;
while(*(str1+i)!='\0')
{
if(*(str1+i)==' ')
{
while(lettercount+1)
{
*(str2+snewcount)=word[lettercount];
snewcount++;
lettercount--;

}

*(str2+snewcount)=' ';
snewcount++;
lettercount=-1;


}
else
{
lettercount++;
word[lettercount]=*(str1+i);

}


i++;


}
while(lettercount+1)
{
*(str2+snewcount)=word[lettercount];
snewcount++;
lettercount--;

}
snewcount++;
lettercount=-1;
*(str2+snewcount)='\0';
return 0;
}


int main()
{
char str[100];
char strnew[100]={'\0'};
printf("\nEnter a string:");
scanf("%[^\n]",str);
printf("\nYou have entered:\n");
puts(str);
printf("\nThe string with reversed words is:\n");
wordrev(str,strnew);
puts(strnew);
return 0;
}
