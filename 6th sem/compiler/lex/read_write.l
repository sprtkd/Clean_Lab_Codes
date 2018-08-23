/*Definition*/
%{
	#include <stdio.h>
	int printc=0;
	int scanc=0;
%}

/*Rule Section*/
%%
[a-zA-Z0-9]+printf[a-zA-Z0-9]* {fprintf(yyout,yytext);}
[a-zA-Z0-9]*printf[a-zA-Z0-9]+ {fprintf(yyout,yytext);}
[a-zA-Z0-9]+scanf[a-zA-Z0-9]* {fprintf(yyout,yytext);}
[a-zA-Z0-9]*scanf[a-zA-Z0-9]+ {fprintf(yyout,yytext);}
printf {printc++;
		fprintf(yyout,"write");}
scanf {scanc++;
		fprintf(yyout,"read");}
%%
	
main()
{
	printf("\nEnter some statements [Press Ctrl+D to exit]:\n");
	yylex();
	yyout = fopen("readwrite.txt","w");
	printf("\nNumber of items counted:\n");
	printf("\n>Printf: %d",printc);
	printf("\n>Scanf: %d\n-------------------------------\n",scanc);
	return 0;
}
