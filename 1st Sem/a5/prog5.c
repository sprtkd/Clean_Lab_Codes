#include <stdio.h>
#define N 100
 
int matlargerowcol(int matrixint[][N], int a,int b)
{
    int i, j,lar,row[N],col[N];




for(i=0;i<a;i++)//row max
{lar=matrixint[i][0];
for(j=0;j<b;j++)
{
if(lar<matrixint[i][j])
lar=matrixint[i][j];

}
row[i]=lar;
}


for(j=0;j<b;j++)//col max
{lar=matrixint[0][j];
for(i=0;i<a;i++)
{
if(lar<matrixint[i][j])
lar=matrixint[i][j];

}
col[j]=lar;
}
puts("\nRow maximums:\n");
for(i=0;i<a;i++)
printf("\n%d",row[i]);

puts("\nColumn maximums:\n");
for(j=0;j<b;j++)
printf("\t%d",col[j]);
  

puts("\n");
return 0;      
}
 
int main()
{
    int mat[N][N],i,j,m,n;

 puts("\nEnter dimension (m,n) of matrix:\n");
scanf("%d,%d",&m,&n);
    puts("\nEnter matrix:\n");
	for(i=0;i<m;i++)
{
for(j=0;j<n;j++)
{
printf("\nEnter element [%d][%d]:",i+1,j+1);
scanf("%d",&mat[i][j]);
}

}

puts("\nEntered matrix:\n");
	for(i=0;i<m;i++)
{printf("\n");
for(j=0;j<n;j++)
{
printf("\t");
printf("%d",mat[i][j]);
}

}

matlargerowcol(mat,m,n);
    return 0;
}
