#include <stdio.h>
#define maxbytes 300

int main(int argc, char* argv[])
{
	FILE *fp;
	long int pos,curr,temp;
	char c;
	if(argc<2)
	{
		printf("Please enter in the format: %s [filename]\n",argv[0]);
		return 0;
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("\nFile could not be opened!\n");
		return 0;
	}
	fseek(fp,0,SEEK_END);
	pos=ftell(fp);
	curr=maxbytes;
	if(curr>pos)
		curr=pos;
	temp = pos-curr;
	fseek(fp,temp,SEEK_SET);
	printf("\n------------------\n\n");
	while(!feof(fp))
	{
		c=fgetc(fp);
		printf("%c",c);
	}
	
	printf("\n\n------------------\n");
	fclose(fp);
	return 0;
}
