#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{

FILE *fc,*fw;
char ch;
 printf("\nRunning program ' %s '",argv[0]);


if ( argc != 3 )
    	{
        printf("\nInvalid parameters!!\nusage: [%s] [file to be copied] [file to be written]",argv[0]);
	exit(1);
	
	}
else
{
printf("\nCopying %s to %s...",argv[1],argv[2]);
fc=fopen(argv[1],"r");
if(fc==NULL)
{
printf("Copying failed!!Cannot open %s.",argv[1]);
exit(1);

}
fw=fopen(argv[2],"w");
if(fc==NULL)
{
printf("Copying failed!!Cannot open %s.",argv[2]);
exit(1);

}

while(1)
{
ch=fgetc(fc);
if(ch==EOF)
break;

fputc(ch,fw);
}
puts("\nCopying suceed!");
fclose(fc);
fclose(fw);
}

return 0;
}
