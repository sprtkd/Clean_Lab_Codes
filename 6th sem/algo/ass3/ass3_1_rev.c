#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXSTR 1000

struct mat_order
{
	int n;
	int m;
};

struct mat_chain
{
	int num;
	struct mat_order *m_order;
};

struct mat_chain_mul_tab
{
	int k;
	long int cost;	
};

void input_mat_chain(struct mat_chain *m_chain)
{
	int i;
	printf("\tEnter the number of matrices(mxn): ");
	scanf("%d",&(m_chain->num));
	m_chain->m_order = (struct mat_order*)malloc((m_chain->num)*sizeof(struct mat_order));
	
	for(i=0;i<(m_chain->num);i++)
	{
		printf("\tEnter (m,n) for matrix %d: ",i+1);
		scanf("%d,%d",&(m_chain->m_order[i].m),&(m_chain->m_order[i].n));
		if(i!=0&&(m_chain->m_order[i].m!=m_chain->m_order[i-1].n))
		{
			printf("\nIncompatible size!\n");
			exit(0);
		}
			
	}
	
}

void MatChainMult_DP(int *list, int tab_size, struct mat_chain_mul_tab table[][tab_size])
{
	int i,j,k,L;
	long int local_cost;
	//zero cost for same start and end
	for(i=1;i<tab_size;i++)
	{
		table[i][i].cost=0;
		table[i][i].k=i;
	}
	
	//other costs
	for (L=2; L<tab_size; L++)
    {
        for (i=1; i<tab_size-L+1; i++)
        {
            j = i+L-1;
            table[i][j].cost = LONG_MAX;
            for (k=i; k<=j-1; k++)
            {
                local_cost = table[i][k].cost + table[k+1][j].cost + list[i-1]*list[k]*list[j];
                if (local_cost < table[i][j].cost)
                {
                    table[i][j].cost = local_cost;
                    table[i][j].k=k;
                    
                }
            }
        }
    }
	
	printf("\nThe DP table is:\n");

	for(i=1;i<tab_size;i++)
	{
		printf("\n");
		for(j=i;j<tab_size;j++)
			printf("%ld,%d\t",table[i][j].cost,table[i][j].k);
	}
	
}

void putBrackets(char *str, int tab_size, struct mat_chain_mul_tab table[][tab_size], int i, int j)
{
	if(i==j)
 	{
    	printf("%c",(char)('A'+i-1));
	}
	else
	{
		printf("(");
  		putBrackets(str, tab_size, table, i,table[i][j].k);
  		putBrackets(str, tab_size, table, (table[i][j].k+1),j);
  		printf(")");
	}
}


void divideMatChain(struct mat_chain m_chain)
{
	int i;
	
	//keeping 1 row and 1 column extra for simplicity of formula
	struct mat_chain_mul_tab mmTable[m_chain.num+1][m_chain.num+1];
	
	int sizeList[m_chain.num+1];
	char str[MAXSTR];
	
	for(i=0;i<MAXSTR;i++)
		str[i] = '\0';
	
	for(i=0;i<=m_chain.num;i++)
	{
		if(i==m_chain.num)
			sizeList[i] = m_chain.m_order[i-1].n;
		else
			sizeList[i] = m_chain.m_order[i].m;
	}
	
	
	//fill up mmtable
	MatChainMult_DP(sizeList,m_chain.num+1,mmTable);
	
	printf("\n\nMatrix Map:\n\n");
	for(i=0;i<m_chain.num;i++)
	{
		printf("%c -> %d,%d\n",(char)('A'+i),m_chain.m_order[i].m,m_chain.m_order[i].n);
	}

	printf("\nThe Bracketed Matrix sequence is:\n");

	//put brackets
	putBrackets(str, m_chain.num+1, mmTable, 1, m_chain.num);
	printf("\n");
}


int main()
{
	struct mat_chain matrix_chain;
	printf("\nEnter the matrix chain information:\n");
	input_mat_chain(&matrix_chain);
	divideMatChain(matrix_chain);
	return 0;
}

