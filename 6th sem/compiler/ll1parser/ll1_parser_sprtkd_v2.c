//ll(1) parser for re
//ll(1) parser is a top down parser without backtracking

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxLenStr 10000
#define NUL_STR "0"
#define EPS "e"

struct ll1_rule
{
	int rule_len;
	char *rule;
};

struct ll1_obj
{
	int non_term_count;
	char *non_terms;
	int term_count;
	char *terms;
	struct ll1_rule *rule_table;
	char *stack;
	int stacktop;
};

struct ll1_rule* ret_rulefromtab(struct ll1_rule *rt, int row, int col, int termct)
{
	//address starts from 0,0
	return &(rt[ (row*termct) + col]);
}

void char_push(char *st,int *top, char c)
{
	if(*top > maxLenStr)
	{
		printf("\nStack overflow!\n");
		return;
	}
		
	(*top)++;
	st[*top] = c;
}

char char_pop(char *st,int *top)
{
	char ch;
	if(*top < 0)
	{
		printf("\nStack Underflow!");
		return '\0';
	}
		
		
	ch = st[*top];
	(*top)--;
	return ch;
}

void print_charStack(char *st,int *top)
{
	int i;
	for(i=0;i<=*top;i++)
	{
		printf("%c",st[i]);
	}
}

void print_input(char *st,int offset)
{
	int i;
	for(i=offset;i<strlen(st);i++)
	{
		printf("%c",st[i]);
	}
}

void initDFA(char *s1, char *s2,struct ll1_obj *d)
{
	d->non_term_count=strlen(s2);
	d->non_terms= (char*)malloc((d->non_term_count+1)*sizeof(char));
	strcpy(d->non_terms,s2);
	d->term_count=strlen(s1) + 1;
	d->terms= (char*)malloc((d->term_count+1)*sizeof(char));
	strcpy(d->terms,s1);
	d->terms[d->term_count - 1] = '$';
	d->terms[d->term_count] = '\0';
	d->rule_table = (struct ll1_rule*)malloc( ( (d->non_term_count)*(d->term_count + 1) ) * sizeof(struct ll1_rule));
	
	d->stack = (char *)malloc(maxLenStr*sizeof(char));
	d->stacktop=-1;
	
	
}

void printParseTable(struct ll1_obj *d)
{
	int i,j;
	char str[maxLenStr];
	struct ll1_rule *curr;
	
	printf("\n\nLL(1) table\n----------------------------------\n\n++++|");

	for(i=0;i<d->term_count;i++)
	{
		printf("\t%c |",d->terms[i]);
	}

	for(i=0;i<d->non_term_count;i++)
	{
		printf("\n%c > |",d->non_terms[i]);
		for(j=0;j<d->term_count;j++)
		{
			struct ll1_rule *curr = ret_rulefromtab(d->rule_table, i,j, d->term_count);
			if(curr->rule_len==0)
			{
				printf("\t-- |");
			}
			else
			{
				printf("\t%s |",curr->rule);
			}
			
		}
	}

	printf("\n----------------------------------\n");
}

void rules_input(struct ll1_obj *d)
{
	int i,j;
	char str[maxLenStr];
	struct ll1_rule *curr;
	printf("\nEnter rules for LL(1) table..\n>No arrows or delimiters needed.\n>e is for epsilon\n>Enter 0 to denote a null string\n\n");
	for(i=0;i<d->term_count;i++)
	{
		for(j=0;j<d->non_term_count;j++)
		{
			printf("\nEnter rule for %c,%c: ",d->non_terms[j],d->terms[i]);
			struct ll1_rule *curr = ret_rulefromtab(d->rule_table, j,i, d->term_count);
			scanf("%s",str);
			if(strcmp(str,NUL_STR)==0)
			{
				printf("NULL string detected..\n");
				curr->rule_len = 0;
				curr->rule = NULL;
			}
			else
			{
				curr->rule_len = strlen(str);
				curr->rule = (char*)malloc((curr->rule_len+1)*sizeof(char));
				strcpy(curr->rule,str);
				printf("You entered: %s\n",curr->rule);
			}
			
		}
	}

	printParseTable(d);
}

int findNonTerm(struct ll1_obj *d, char ch)
{
	int i;
	for(i=0;i<d->non_term_count;i++)
	{
		if(d->non_terms[i] == ch)
			return i;
	}
	return -1;
}

int findTerm(struct ll1_obj *d, char ch)
{
	int i;
	for(i=0;i<d->term_count;i++)
	{
		if(d->terms[i] == ch)
			return i;
	}
	return -1;
}

void parseRE(struct ll1_obj *d, char *input)
{
	char topchar;
	struct ll1_rule *temp_r;
	int i=0, pos_nt,pos_t, j;

	printf("\nParsing...\n");

	printf("\nStack |\tInput |\tResult\n------------------------------\n");

	char_push(d->stack,&(d->stacktop),'$');
	char_push(d->stack,&(d->stacktop),d->non_terms[0]);
	
	j= strlen(input);
	input[j+1]='\0';
	input[j]='$';

	while(input[i]!='\0')
	{
		printf("\n");
		print_charStack(d->stack,&(d->stacktop));
		printf(" |\t");
		print_input(input,i);
		printf(" |\t");
		topchar = char_pop(d->stack,&(d->stacktop));
		//termination
		if(topchar=='$')
		{
			if(topchar == input[i])
			{
				printf("Accept");
				printf("\n***Voila! The RE was parsed..***\n");
				break;
			}
			else
			{
				printf("\n--The RE failed to parse!!\n");
				break;
			}
		}
		
		
		if(topchar == input[i])
		{
			printf("%c passed.", input[i]);
			i++;
		}
		else
		{
			pos_nt = findNonTerm(d, topchar);
			pos_t = findTerm(d, input[i]);
			if(pos_t<0 || pos_nt<0)
			{
				printf("\n--Error! No parse table entry found %d,%d\n",pos_nt,pos_t);
				return;
			}
			
			temp_r = ret_rulefromtab(d->rule_table , pos_nt, pos_t, d->term_count);
			
			if(temp_r->rule_len<=0)
			{
				printf("\n--No rule found for %c,%c.. Parsing terminated!\n",topchar,input[i]);
				break;
			}

			printf("%c -> ",topchar);
			
			for(j=0; j<temp_r->rule_len; j++)
			{
				printf("%c",temp_r->rule[j]);
			}

			if(strcmp(temp_r->rule,EPS)==0)
			{
				printf("(epsilon)");
			}
			else
			{
				for(j=(temp_r->rule_len)-1; j>=0;j--)
				{
					char_push(d->stack, &(d->stacktop), temp_r->rule[j]);
				}
			}
			
			
		}
	}
	
}


int main()
{

	char str1[maxLenStr],str2[maxLenStr],inp[maxLenStr];
	struct ll1_obj ll1;
	
	//take input
	printf("\nEnter the terminals (no delimiters) :\n");
	scanf("%s",str1);
	printf("\nEnter the non-terminals  (no delimiters) (put start symbol at first) :\n");
	scanf("%s",str2);
	printf("\nEnter the input string:\n");
	scanf("%s",inp);
	initDFA(str1, str2,&ll1);
	rules_input(&ll1);
	parseRE(&ll1,inp);
	
	return 0;
}
