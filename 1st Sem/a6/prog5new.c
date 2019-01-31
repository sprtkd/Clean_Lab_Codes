#include<stdio.h>

struct wordstr
{
char word[100];
int len;

};
struct wordstr wordstring[100];

char* largestword(char *rstr)
{
int i,iword,jword,wordlen,g;

wordlen=0;
iword=0;
jword=0;
for(i=0;rstr[i]!='\0';i++)
{
if((rstr[i]==' ')||(rstr[i]=='.'))
{
if(wordlen)
{
wordstring[iword].word[jword]='\0';
wordstring[iword].len=wordlen;
iword++;
}
wordlen=0;
jword=0;


}
else
{
wordstring[iword].word[jword]=rstr[i];
wordlen++;
jword++;
}
}

if(wordlen)
{
wordstring[iword].word[jword]='\0';
wordstring[iword].len=wordlen;
}

g=iword;
while(iword+1)
{
if(wordstring[iword].len>wordstring[g].len)
g=iword;
iword--;
}




return wordstring[g].word;
}









int main()
{

char str[100];

printf("\nEnter a string:");
scanf("%[^\n]",str);
printf("\nYou have entered:\n");
puts(str);



puts("\nThe largest word is:\n");
puts(largestword(str));
return 0;
}
