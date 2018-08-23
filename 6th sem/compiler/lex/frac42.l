/*Definition*/
%{
	#include <stdio.h>
	int frac=0;
	int integer=0;
%}

digs [0-9]
dig3 [3-9]
dig5 [5-9]
/*Rule Section*/
%%
[4][3-9][.][[0-9]*][1-9] {frac++;}
[5-9][0-9][.][[0-9]*][1-9] {frac++;}
[0-9][0-9][[0-9]+][.][[0-9]*][1-9] {frac++;}

[4][3-9][.][[0]*] {integer++;}
[5-9][0-9][.][[0]*] {integer++;}
[0-9][0-9][[0-9]+][.][[0]*] {integer++;}

[4][3-9] {integer++;}
[5-9][0-9] {integer++;}
[0-9][0-9][[0-9]+] {integer++;}
%%
	
main()
{
	printf("\nEnter some text [Press Ctrl+D to exit]:\n");
	yylex();
	printf("\nNumber of items counted:\n");
	printf("\n>Fractions greater than 42: %d\n-------------------------------\n",frac);
	printf("\n>Fractions greater than 42: %d\n-------------------------------\n",integer);
	return 0;
}
