/*Definition*/
%{
	#include <stdio.h>
	int chars=0;
	int words=0;
	int spaces=0;
	int lines=0;
%}
 
/*Rule Section*/
%%
[a-zA-Z0-9]+ {words++;
		chars = chars + yyleng;}
[ ] {spaces++;}
[\n] {lines++;}
%%
	
main()
{
	printf("\nEnter some statements [Press Ctrl+D to exit]:\n");
	
	yylex();
	
	printf("\nNumber of items counted:\n");
	printf("\n>Characters: %d",chars);
	printf("\n>Spaces: %d",spaces);
	printf("\n>Lines: %d",lines);
	printf("\n>Words: %d\n-------------------------------\n",words);
	return 0;
}
