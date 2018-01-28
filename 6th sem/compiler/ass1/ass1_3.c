//Made by suprotik dey

/*
Made by
Suprotik
Dey
*/

#include <stdio.h>
#include <string.h>
#define max 1000

int main()
{
	char str[max];
	int i,count=0;
	//count variable counts number of whitespaces
	printf("\nEnter a string:\n");
	scanf("%[^\n]",str);
	/*
	for input until newline
	%[^\n] is used*/
	for(i=0;i<strlen(str);i++)
		if(str[i]==' ')
			count++;
	printf("Number of whitespaces: %d\n",count);
	//printing
	count=count/2;
	return 0;
}
