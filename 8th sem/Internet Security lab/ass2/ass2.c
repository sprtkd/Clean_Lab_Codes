#include <stdio.h>
#define MAXFILENAMELEN 100
#define KEYSIZE 16
#define ZSIZE 251
#define VERBOSE 0
#define ENC_FILE "encrypted.txt"
#define DEC_FILE "decrypted.txt"

//====================Multiplicative Inverse===============================
int ExtendedGCD(int a, int b, int *x, int *y) 
{ 
    if (b == 0)
    {
    	*x = 1;
    	*y = 0;
        return a;
    }
    int currGCD, prev_x,prev_y;
    currGCD = ExtendedGCD(b, a % b, &prev_x, &prev_y);
    *x = prev_y;
    *y = prev_x - (a/b)*prev_y;
    return currGCD;
}

int normalizeInverse(int x,int n)
{
	if(x>0)
		return x%n;
	else
		return normalizeInverse(n+x,n);
}

int multiplicativeInverse(int a, int n)
{
	int x,y,g;
	g = ExtendedGCD(a,n,&x,&y);
	if(g==1)
		return normalizeInverse(x,n);
	else
	{
		printf("Noinverse!!");
		return 0;
	}
}
//====================Multiplicative Inverse===============================

int encrypter(char plainChar, char *k1, char *k2, int counter)
{
	int cipherChar;
		
	cipherChar = ((plainChar*(k1[counter]-'0'))+(k2[counter]-'0'))%ZSIZE;
	if(VERBOSE)
		printf("k1 %d - k2 %d - counter %d",(k1[counter]-'0'),(k2[counter]-'0'),counter);
	return cipherChar;
}

char decrypter(int cipherChar, char *k1, char *k2, int counter)
{
	int plainChar;
		
	plainChar = ((cipherChar - (k2[counter]-'0'))*multiplicativeInverse(k1[counter]-'0',ZSIZE))%ZSIZE;
	return plainChar;
}

int main()
{
	char filename[MAXFILENAMELEN], currPlainTextChar,k1[KEYSIZE+1],k2[KEYSIZE+1];
	int kkk,kk2;
	FILE *fp, *fp2, *fp3;
	int counter_i;
	printf("Enter File Name: ");
	scanf("%[^\n]",filename);
	fp = fopen(filename, "r");
	fp2 = fopen(ENC_FILE, "w");
	fp3 = fopen(DEC_FILE, "w");
	if(fp==NULL)
	{
		printf("Cannot Open File!\n");
		return 0;
	}
	
	printf("Enter key 1: ");
	scanf("%s",k1);
	printf("Enter key 2: ");
	scanf("%s",k2);
	
	printf("\n>>Encrypting....\n\n");
	counter_i=0;
	while((currPlainTextChar=fgetc(fp))!=EOF)
	{
		if(VERBOSE)
			printf("%c  %d  ",currPlainTextChar,currPlainTextChar);
		
		kkk = encrypter(currPlainTextChar,k1,k2,counter_i);
		if(VERBOSE)
			printf("  %d  %c    %c \n",kkk,kkk,decrypter(kkk,k1,k2,counter_i));
		fputc(kkk,fp2);
		counter_i = (counter_i+1)%KEYSIZE;
	}
	
	fclose(fp);
	fclose(fp2);
	printf("Encryption saved as %s...\n",ENC_FILE);
	fp2 = fopen(ENC_FILE, "r");
	if(fp2==NULL)
	{
		printf("Cannot Open File!\n");
		return 0;
	}
	printf("\n>>Decrypting....\n\n");
	counter_i=0;
	while((kkk=fgetc(fp2))!=EOF)
	{
		currPlainTextChar = decrypter(kkk,k1,k2,counter_i);
		printf("%c",currPlainTextChar);
		fputc(currPlainTextChar,fp3);
		counter_i = (counter_i+1)%KEYSIZE;
	}
	fclose(fp3);
	fclose(fp2);
	return 0;
}
