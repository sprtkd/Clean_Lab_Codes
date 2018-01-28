#include <stdio.h>
#include <string.h>
#define BUF_LEN 1024


int flag=0;
/*
	0 nothing
	1 / found probability of comment
	2 * found start of multiline comment
	3 * found end of comment probably
	4 / found single line comment start
	
*/

void printComment(char c)
{
	if(flag==0)
	{
		if(c=='/')
		{
			flag=1;
			return;
		}
			
	}
	
	if(flag==1)
	{
		if(c=='/')
		{
			flag=4;
			printf("\nSingle line comment:\n");
			return;
		}
		else if(c=='*')
		{
			flag=2;
			printf("\nMulti line comment:\n");
			return;
		}
		else
		{
			flag=0;
			return;
		}
		
		
	}
	
	if(flag==2)
	{
		if(c=='*')
		{
			flag=3;
			return;
		}
		else
		{
			
			printf("%c",c);
			return;
		}
		
		
	}
	
	if(flag==3)
	{
		if(c=='/')
		{
			flag=0;
			return;
		}
		else
		{
			flag=2;
			return;
		}
		
		
	}
	
	if(flag==4)
	{
		if(c=='\n')
		{
			flag=0;
			return;
		}
		else
		{
			printf("%c",c);
			return;
		}
		
		
	}
		
}

int main()
{
	char path_f[BUF_LEN],ch;
	
	FILE *fp_code;
	
	printf("\nEnter the path of c code: ");
	scanf("%s",path_f);
	
	fp_code = fopen(path_f,"r");
	
	if(fp_code==NULL)
		printf("\nFile open failed!");
	else
		printf("\nFile successfully opened!");
	printf("\n");
	
	while(1)
	{
		ch=fgetc(fp_code);
		if(ch==EOF)
			break;
		printComment(ch);
	}
	printf("\n");
	return 0;
}
