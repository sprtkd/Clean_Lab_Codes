#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//object virtualization of NFA
struct array_int
{
	int array[MAX];
};

struct mat_2d_int
{
	struct array_int arr[MAX];
};

struct NFA
{
	int num_of_states;
	int num_of_inputs;
	struct mat_2d_int mat[MAX];
};

struct NFA *init_NFA(int s,int inp)
{
	struct NFA *nfa;
	nfa = (struct NFA*)malloc(sizeof(struct NFA));
	nfa->num_of_inputs = inp;
	nfa->num_of_states = s;
	
	int i,j,k;
	for(i=0;i<s;i++)
	{
		for(j=0;j<inp;j++)
		{
			for(k=0;k<MAX;k++)
			{
				nfa->mat[i].arr[j].array[k] = 0;
			}
		}
		
	}
	
	return nfa;
}

struct NFA *input_NFA_eps()
{
	struct NFA *nfa;
	int i,j,k;
	char str[MAX];
	int nfa_eps_states, nfa_eps_input;
	printf("\nEnter the number of states in nfa: ");
	scanf("%d",&nfa_eps_states);
	printf("\nEnter the number of inputs in nfa: ");
	scanf("%d",&nfa_eps_input);
	nfa = init_NFA(nfa_eps_states,nfa_eps_input+1);
	
	printf("\nEnter the delta functions (Enter string for multiple inputs)");
	
		printf("\nStates\t| Inputs\t| Output States\n");
	printf("--------------------------------------------\n");
	
	for(i=0;i<(nfa->num_of_states);i++)
	{
		for(j=0;j<(nfa->num_of_inputs);j++)
		{
			printf("\nS%d\t  ",i+1);
			printf("I%d\t: ",j+1);
			scanf("%s",str);
			for(k=0;k<strlen(str);k++)
			{
				if((str[k] - '0') - 1 >=0)
					nfa->mat[i].arr[j].array[(str[k] - '0') - 1] = 1;
				
			}
		}
	}
	return nfa;
}

void print_NFA(struct NFA *nfa)
{
	printf("\nStates\t| Inputs\t| Output States\n");
	printf("--------------------------------------------\n");
	int i,j,k;
	for(i=0;i<(nfa->num_of_states);i++)
	{
		for(j=0;j<(nfa->num_of_inputs);j++)
		{
			printf("\nS%d\t  ",i+1);
			printf("I%d\t",j+1);
			for(k=0;k<(nfa->num_of_states);k++)
			{
				if(nfa->mat[i].arr[j].array[k])
					printf("S%d,",k+1);
			}
		}
	}
	
}
//object virtualization of NFA



int main()
{
	struct NFA *nfa_eps;

	//input
	nfa_eps = input_NFA_eps();
	//print data
	print_NFA(nfa_eps);
	//find and store epsilon closure
	
	//build transition table
	
	//print dfa
	return 0;
}
