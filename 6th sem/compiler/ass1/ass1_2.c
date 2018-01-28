#include <stdio.h>
#define BUF_LEN 1000
int flag=0;
/*
0 nothing
1 variable name started
2 number with digit started
3 decimal point found real number may be started
4 number after decimal point real number may be started
5 E found exponent
6 E 2nd letter

*/

int isDigit(char c)
{
	if(c>='0'&&c<='9')
		return 1;
	return 0;
}

int isChar(char c)
{
	if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
		return 1;
	return 0;
}

int isDelimiter(char c)
{
	if(c==' '||c=='\n'||c=='\t'||c=='+'||c=='-'||c=='*'||c=='/'||c==','||c==';'||c=='.')
		return 1;
	return 0;
}


void classifyNumbers(char c)
{
	switch(flag)
	{
		//start
		case 0: if(isDigit(c))
				{
					flag=2;
					printf("\nNumber started: ");
					printf("%c",c);
				}
				else if(c=='.')
				{
					flag=3;
					printf("\nNumber started: ");
					printf("%c",c);
				}
				else if(isChar(c))
				{
					flag=1;
					printf("\nVariable started: ");
					printf("%c",c);
				}
				
				break;
		//variable
		case 1: if(isDelimiter(c))
				{
					flag=0;
					printf("\n"); 
				}
				
				else
					printf("%c",c);
				break;
		//integer		
		case 2: if(isDigit(c))
					printf("%c",c);
				else if(c=='.')
				{
					flag=3;
					printf("%c",c);
				}
				else if(c=='E')
				{
					flag=5;
					printf("%c",c);
				}
				else
				{
					flag=0;
					printf("\t<--This is an integer\n");
					classifyNumbers(c);
				}
				break;
		//real number(point found)
		case 3: if(isDigit(c))
				{
					flag=4;
					printf("%c",c);
				}
				else if(c=='E')
				{
					flag=5;
					printf("\b%c",c);
				}
				else
				{
					flag=0;
					printf("\t<--This is an integer\n");
					classifyNumbers(c);
				}
				break;
		//really real number
		case 4: if(isDigit(c))
				{
					printf("%c",c);
				}
				else if(c=='E')
				{
					flag=5;
					printf("%c",c);
				}
				else
				{
					flag=0;
					printf("\t<--This is a real number\n");
					classifyNumbers(c);
				}
		
				break;
				
		//Exponent
		case 5: if(isDigit(c))
				{
					flag=6;
					printf("%c",c);
				}
				else if(c=='+'||c=='-')
				{
					flag=6;
					printf("%c",c);
				}
				else
				{
					flag=0;
					printf("0\t<--This is an exponent\n");
					classifyNumbers(c);
				}
				break;
		//exponent with + or - or none
		case 6: if(isDigit(c))
				{
					printf("%c",c);
				}
				else
				{
					flag=0;
					printf("\t<--This is an exponent\n");
					classifyNumbers(c);
				}
				break;
		
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
		classifyNumbers(ch);
	}
	printf("\n");
	return 0;
}
