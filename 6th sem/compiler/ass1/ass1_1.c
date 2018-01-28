#include <stdio.h>

#define BUF_LEN 1024
#define BUF_END BUF_LEN-1
#define BUF_MID (BUF_LEN/2)-1
#define numofdelims 5

int changeToken=0;

int isDelim(char c)
{
	int i;
	char BUF_DELIMS[numofdelims] = ",\n\t ;";
	
	for(i=0;i<numofdelims;i++)
	{
		if(c==BUF_DELIMS[i]||c==EOF)
			return 1;
	}
	return 0;
}


void printToken(char *dbuf,int first_ptr,int fwd_ptr)
{
	int i;
	for(i=first_ptr;i<=fwd_ptr;i++)
	{
		printf("%c",dbuf[i]);
	}
}

void lex_analyser(char *dbuf, int *ptr, int *bplace)
{
	
	int first_ptr, fwd_ptr;
	
	if(*bplace==0)
	{
		first_ptr=0;
		fwd_ptr=0;
		while(fwd_ptr<=*ptr)
		{
			if(isDelim(dbuf[fwd_ptr]))
			{
				printToken(dbuf,first_ptr,fwd_ptr-1);
				first_ptr=fwd_ptr+1;
				if(changeToken==0)
					printf("\n");//change token
				changeToken=1;
			}
			else
				changeToken=0;
			fwd_ptr++;
		}
		*bplace=1;
		*ptr=BUF_MID+1;
		printToken(dbuf,first_ptr,BUF_MID);
	}
	else
	{
		first_ptr=BUF_MID+1;
		fwd_ptr=BUF_MID+1;
		while(fwd_ptr<=*ptr)
		{
			if(isDelim(dbuf[fwd_ptr]))
			{
				printToken(dbuf,first_ptr,fwd_ptr-1);
				first_ptr=fwd_ptr+1;
				if(changeToken==0)
					printf("\n");//change token
				changeToken=1;
			}
			else
				changeToken=0;
			fwd_ptr++;
		}
	
		*bplace=0;
		*ptr=0;
		printToken(dbuf,first_ptr,BUF_END);
	}
	
}


void load_buffer_proc(FILE *fp)
{

	char double_buf[BUF_LEN],ch;
	int ptr=0, buf_place=0;
	
	
	while(1)
	{
		ch=fgetc(fp);
		
		double_buf[ptr] = ch;
		
		if(ptr==BUF_MID||ptr==BUF_END)
		{
			lex_analyser(double_buf,&ptr,&buf_place);
		}
		
		
		ptr = (ptr+1)%BUF_LEN;
		
		
		if(ch==EOF)
			break;
	}
}



int main()
{
	
	char path_f[BUF_LEN];
	
	FILE *fp_code;
	
	printf("\nEnter the path of c code: ");
	scanf("%s",path_f);
	
	fp_code = fopen(path_f,"r");
	
	if(fp_code==NULL)
		printf("\nFile open failed!");
	else
		printf("\nFile successfully opened!");
	printf("\n");
	load_buffer_proc(fp_code);
	
	return 0;
}
