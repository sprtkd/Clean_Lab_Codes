#include <stdio.h>
#define N 100
 
int matlarge(int matrixint[][N], int a,int b)
{
    int i, j,lar;
lar=matrixint[0][0];


for(i=0;i<a;i++)
{
for(j=0;j<b;j++)
{
if(lar<matrixint[i][j])
lar=matrixint[i][j];

}

}


  return lar;      
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

printf("\nLargest integer in matrix is:%d.",matlarge(mat,m,n));
    return 0;
}
