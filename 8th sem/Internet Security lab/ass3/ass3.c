#include <stdio.h>
#include <string.h>
#define MAXKEYLEN 26
#define MATLEN 5
#define REPLACER 'x'

void keyFiller(char *key, char (*mat)[MATLEN])
{
	int i,j, marker[255]={0}, iterkey,iterfiller, flag=0;
	
	for(i=0; i<strlen(key); i++)
	{
		if(key[i]<'a'||key[i]>'z')
			key[i]=REPLACER;
		if(key[i]=='j')
			key[i]='i';
	}
	
	for(i=0; i<MATLEN; i++)
	{
		for(j=0; j<MATLEN; j++)
		{
			mat[i][j]=0;
		}
	}
	
	
	iterkey=0;
	iterfiller=0;
	for(i=0; i<MATLEN; i++)
	{
		for(j=0; j<MATLEN; j++)
		{
			if(iterkey<strlen(key))
			{
				while(iterkey<strlen(key)) //loop until key is finished
				{
					if(marker[key[iterkey]]==0) //check if absent
					{
						mat[i][j]=key[iterkey];
						marker[mat[i][j]]=1;
						iterkey++;
						break;
					}
					else
					{
						iterkey++;
					}
				}
				
				if(mat[i][j]==0)
					flag=1;
			}
			else
				flag=1;
			
			if(flag)
			{
				while(marker['a'+iterfiller]==1)
					iterfiller++;
				
				if('a'+iterfiller=='j')
					iterfiller++;
					
				while(marker['a'+iterfiller]==1)
					iterfiller++;
				
				mat[i][j]='a'+iterfiller;
				marker[mat[i][j]]=1;
				iterfiller++;
			}
			
		}
	}
}

void showKeyMatrix(char (*mat)[MATLEN])
{
	int i,j;
	for(i=0; i<MATLEN; i++)
	{
		printf("\n");
		for(j=0; j<MATLEN; j++)
		{
			printf("%c\t",mat[i][j]);
		}
	}
	printf("\n");
}

playfairProcessor(char (*d)[2], char (*mat)[MATLEN])
{
	int posr1,posc1,posr2, posc2, i, j;
	
	for(i=0; i<MATLEN; i++)
	{
		for(j=0; j<MATLEN; j++)
		{
			if(mat[i][j] == d[0] )
				break;
		}
	}
	posr1 = i;
	posc1 = j;
	
	for(i=0; i<MATLEN; i++)
	{
		for(j=0; j<MATLEN; j++)
		{
			if(mat[i][j] == d[1] )
				break;
		}
	}
	posr2 = i;
	posc2 = j;
	
	if(posr1 != posr2 && posc1 != posc2)
	{
		d[0] = mat[posr1][posc2];
		d[1] = mat[posr2][posc1];
	}
	
	
}

void playfair_parser(FILE *fp, char (*mat)[MATLEN])
{
	char duo[3],c;
	int i;
	duo[2]='\0';
	
	i=0;
	while((c=fgetc(fp))!=EOF)
	{
		if(c<'a'||c>'z')
			continue;
		else
		{
			i=i%2;
			duo[i]=c;
			i++;
			
			if(duo[i]=='j')
				duo[i]=i;
		}
		
		if(i==2)
		{
			if(duo[0]==duo[1])
				duo[1]=REPLACER;
			printf("%s\n",duo);
		}
	}
	if(i==1)
	{
		duo[i]=REPLACER;
		printf("%s\n",duo);
	}
	
}

int main()
{
	char key[MAXKEYLEN], play_matrix[MATLEN][MATLEN], filename[MAXKEYLEN];
	FILE *fp;
	printf("Enter Key: ");
	scanf("%s",key);
	keyFiller(key,play_matrix);
	printf("\nThe Final key matrix is:\n");
	showKeyMatrix(play_matrix);
	printf("Enter filename: ");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("Could not open file\n");
		return 0;
	}
	
	playfair_parser(fp,play_matrix);
	
	return 0;
}
