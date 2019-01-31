#include <stdio.h>
#include <stdlib.h>//only used for using exit fn..

int main ( int argc, char *argv[] )
{

FILE *fc,*fw;
char c1,c2,flag;
 printf("\nRunning program ' %s '",argv[0]);


if ( argc != 3 )
    	{
        printf("\nInvalid parameters!!\nusage: [%s] [file1 to be checked] [file2 to be checked]",argv[0]);
	exit(1);
	
	}
else
{
printf("\nComparing %s to %s...",argv[1],argv[2]);
fc=fopen(argv[1],"r");
if(fc==NULL)
{
printf("Operation failed!!Cannot open %s.",argv[1]);
exit(1);

}
fw=fopen(argv[2],"r");
if(fc==NULL)
{
printf("Operation failed!!Cannot open %s.",argv[2]);
exit(1);

}

while(1)
{
c1=fgetc(fc);
c2=fgetc(fw);
if(c1!=c2)
{
flag=0;
break;

}
else
flag=1;

if((c1==EOF)||(c2==EOF))
break;
}


fclose(fc);

fclose(fw);
printf("\n%d.",flag);
}

return 0;
}
