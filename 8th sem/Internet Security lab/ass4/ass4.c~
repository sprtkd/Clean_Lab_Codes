#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAXLEN 100

void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void generatePermute(int *arr, int n)
{
	int i;
	for (i=0; i<n; i++) 
		arr[i] = i;

    srand ( time(NULL) ); 
    for (i = n-1; i > 0; i--) 
    {
        int j = rand() % (i+1); 
        swap(&arr[i], &arr[j]); 
    } 
}

void printArray(int *arr, int n) 
{
	int i;
    for (i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void TranspositionEncrypter(FILE *fp, char (*mat)[MAXLEN], char (*matEncrypt)[MAXLEN], int *key, int keysize)
{
	//fill
	char c;
	int i=0,j=0;
	while((c=fgetc(fp))!=EOF)
	{
		if(i==keysize)
			j++;
		i=i%keysize;
		mat[i][j] = c;
		i++;
	}
	printf("\nOriginal: \n");
	for(i=0; i<keysize; i++)
		puts(mat[i]);
	
	
	for(i=0; i<keysize; i++)
		strcpy(matEncrypt[key[i]], mat[i]);
	
	printf("\nEncrypted: \n");
	for(i=0; i<keysize; i++)
		puts(matEncrypt[i]);
}

void TranspositionDecrypter(char (*matEncrypt)[MAXLEN], char (*matDecrypt)[MAXLEN], int *key, int keysize)
{
	//fill
	char c;
	int i=0,j=0, decryptKey[MAXLEN];
	
	for(i=0; i<keysize; i++)
	{
		decryptKey[key[i]] = i;
	}
	
	
	for(i=0; i<keysize; i++)
		strcpy(matDecrypt[decryptKey[i]], matEncrypt[i]);
	
	printf("\nDecrypted: \n");
	for(i=0; i<MAXLEN ; i++)
	{
		for(j=0; j<keysize; j++)
		{
			printf("%c",matDecrypt[j][i]);
		}
	}
}

void cleanCharArr(char (*mat)[MAXLEN])
{
	int i,j;
	for(i=0; i<MAXLEN; i++)
		for(j=0; j<MAXLEN; j++)
			mat[i][j] = '\0';
	
}

int main()
{
	int keysize, permuteKey[MAXLEN];
	char filename[MAXLEN];
	char originalMat[MAXLEN][MAXLEN], cipherMat[MAXLEN][MAXLEN];
	cleanCharArr(cipherMat);
	FILE *fp;
	printf("Enter key size: ");
	scanf("%d",&keysize);
	generatePermute(permuteKey, keysize);
	printf("The key generated: ");
	printArray(permuteKey, keysize);
	printf("Enter Filename: ");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("Could not open file\n");
		return;
	}
	TranspositionEncrypter(fp, originalMat, cipherMat, permuteKey, keysize);
	TranspositionDecrypter(cipherMat, originalMat,  permuteKey, keysize);
	return 0;
}
