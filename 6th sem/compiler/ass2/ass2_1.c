#include <stdio.h>
#include <stdlib.h>
#define max 100

struct stateTable
{
	int states[max];
};

void showMap(int s, int ip)
{
	int i;
	char c='a';
	printf("\nMap:\nStates:\n");
	for(i=1;i<=s;i++)
		printf("S%d, ",i);
	printf("\n");
	
	printf("\nInputs:\n");
	for(i=1;i<=ip;i++,c++)
		printf("%c==>%d, ",c,i);
	printf("eps==>%d",ip+1);
	printf("\n");
	
}


void showDels(int (*mat)[max], int ns, int nfa_input)
{
	int i,j;
	for(i=0;i<ns;i++)
	{
		for(j=0;j<=nfa_input;j++)
		{
			if(mat[i][j]>=0)
				printf("\ndel(S%d, ip%d) -> S%d",i+1,j+1,mat[i][j]+1);
			
		}
	}
}

void storeEpsClosure(int (*mat)[max], int (*mateps)[max],int ns, int eppos)
{
	//first position will store number of elements at each closure
	int i,j;
	for(i=0;i<ns;i++)
	{
		mateps[i][0]=1;
		mateps[i][1]=i;
		if(mat[i][eppos]>0)
		{
			mateps[i][2]=mat[i][eppos];
			(mateps[i][0])++;
		}
	}
	
	printf("\n\nEpsilon Closure:\n");
	for(i=0;i<ns;i++)
	{
		printf("\nS%d : {",i+1);
		for(j=1;j<=mateps[i][0];j++)
			printf("%d,",mateps[i][j]+1);
		printf("}\n");
	}
	
	
}

void setStateinTable(struct stateTable *state_tab_node, int *eps)
{
	int i;
	for(i=1; i<=eps[0]; i++)
	{
		state_tab_node->states[i-1]=1;
	}
	
}

int checkifStateExist(struct stateTable *state_tab,int last_row_stored,struct stateTable new_added_node,int nstates, int ninputs)
{
	int i,j;
	for(i=0;i<=last_row_stored;i++)
	{
		for(j=0;j<nstates;j++)
		{
			if(state_tab[(i*(ninputs+1)) ].states[j] != new_added_node.states[j])
				return 0;
		}
		
	}
	
	return 1;
}

struct stateTable *constructtransitiontable(int *numofst, int (*mat_eps)[max], int nstates, int ninputs, int (*mat_nfa)[max])
{
	int i,j,k,curr_out;
	struct stateTable *state_tab;
	int last_row_stored=-1, last_row_computed=-1;
	
	state_tab = (struct stateTable *)malloc(max*max*sizeof(struct stateTable));
	
	
	
	//init state table
	for(i=0;i<max;i++)
	{
		for(j=0;j<=ninputs;j++)
		{
			for(k=0;k<nstates;k++)
				state_tab[(i*(ninputs+1))+j].states[k]=0;
		}
	}
	
	//enter the initial state
	setStateinTable(&(state_tab[0]), mat_eps[0]);
	last_row_stored++;
	printf("New state entered...\n");
	/*
	while there is a new state
	compute output for each input 
	compute epsilon closure
	store
	if new output state found, store it
	*/
	while(last_row_computed<last_row_stored)
	{
		for(i=0;i<nstates;i++)
		{
			if(state_tab[((last_row_computed+1)*(ninputs+1))+0].states[i])
				for(j=0;j<ninputs;j++)
				{
					//compute the output for particular input and current row
					curr_out = mat_nfa[i][j];
					//store the epsilon closure
					setStateinTable(&(state_tab[((last_row_computed+1)*(ninputs+1))+ (j+1) ]), mat_eps[curr_out]);
					//check if state is new, if new add it
					if(checkifStateExist(state_tab,last_row_stored,state_tab[((last_row_computed+1)*(ninputs+1))+ (j+1) ], nstates, ninputs)==0)
					{
						printf("New state entered...\n");
						last_row_stored++;
						setStateinTable(&(state_tab[((last_row_stored)*(ninputs+1))+ 0 ]), mat_eps[curr_out]);
					}
				}
		}
		last_row_computed++;
	}
	printf("\nTotal number of states in dfa : %d",last_row_computed+1);
	*numofst=last_row_computed;
	return state_tab;
}

void printtransitiontable(struct stateTable *state_tab,int state_tab_size,int nfa_states, int nfa_input)
{
	printf("\nDFA state table:\n\n");
	
	int i,j,k;
	
	printf("Dfa states");
	for(i=1;i<=nfa_input;i++)
	{
		printf("\t%d",i);
	}
	printf("\n");
	printf("-------------------------------------------------\n");
	
	for(i=0;i<=state_tab_size;i++)
	{
		for(j=0;j<=nfa_input;j++)
		{
			for(k=0;k<nfa_states;k++)
			{
				printf("%d,",state_tab[(i*(nfa_input+1)) +j].states[k]);
			}
			printf("\t");
		}
		printf("\n");
	}
}

int main()
{
	int nfa_states, nfa_input,nfa_state_matrix[max][max],i,j,k;
	//state matrix will contain all with offset of -1
	int nfa_closure_matrix[max][max];
	struct stateTable *state_table;
	int state_table_size;
	printf("\nEnter the number of states in nfa: ");
	scanf("%d",&nfa_states);
	printf("\nEnter the number of inputs in nfa: ");
	scanf("%d",&nfa_input);
	
	showMap(nfa_states, nfa_input);
	
	
	printf("\nEnter Deltas (enter 0 if not present):");
	for(i=0;i<nfa_states;i++)
	{
		for(j=0;j<=nfa_input;j++)
		{
			printf("\nEnter del(S%d, ip%d): ",i+1,j+1);
			scanf("%d",&k);
			nfa_state_matrix[i][j]=k-1;
		}
	}
	
	showDels(nfa_state_matrix,nfa_states, nfa_input);
	storeEpsClosure(nfa_state_matrix,nfa_closure_matrix,nfa_states, nfa_input);
	
	
	state_table = constructtransitiontable(&state_table_size , nfa_closure_matrix, nfa_states, nfa_input, nfa_state_matrix);
	printtransitiontable(state_table,state_table_size,nfa_states, nfa_input);
}
