#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 10000

//tokenise-------------
struct tokenNode
{
	char symbol1;
	char op;
	char symbol2;
	void *littleArray1;//call tokenArray typecast
	void *littleArray2;//call tokenArray typecast

	//store NULL or 0 if nothing is present
};

struct tokenArray
{
	struct tokenNode *list;
	int tokenCount;
};
//tokenise-------------


int normalizeRE(char *re)
{
	//this will cleanup re and remove stray spaces and extra characters
	//and any error in re return 1;

	int i,j,len, top;
	char brackets[MAX];
	len =strlen(re);

	//enter # to mark end
	re[len]='#';
	re[len+1]='\0';
	len=len+1;

	//space cleanup and stray operator
	for(i=0;i<len;i++)
	{
		if(re[i]==' ')
		{
			for(j=i;j<len;j++)
				re[j] = re[j+1];
			i--;
			len--;
		}

		if(!(re[i]=='*'||re[i]=='|'||re[i]==' '||re[i]=='+'||re[i]=='('||re[i]==')'||(re[i]>='A'&&re[i]<='Z')||(re[i]>='a'&&re[i]<='z')||(re[i]>='0'&&re[i]<='9')||re[i]=='#'))
		{
			printf("Stray operator/symbol '%c' at %d!\n",re[i],i+1);
			return 1;
		}

	}

	//unwanted repeated operator detection
	for(i=0;i<len-1;i++)
	{
		if(((re[i]=='*'||re[i]=='|'||re[i]=='+'||re[i]=='#')&&(re[i] == re[i+1]))||(re[i]=='*'&&re[i+1]=='+')||(re[i]=='+'&&re[i+1]=='*'))
		{
			printf("Wrongly repeated operator '%c' at %d!\n",re[i],i+1);
			return 1;
		}
	}

	//check paranthesis
	top=0;
	for(i=0;i<len;i++)
	{
		if(re[i]=='(')
		{
			brackets[top++]='(';
		}
		else if(re[i]==')')
		{
			if((top>0)&&(brackets[top-1]=='('))
				top--;
			else
			{
				printf("Parenthesis not matching at %d!\n",i+1);
				return 1;
			}
		}
	}

	if(top!=0)
	{
		printf("Parenthesis not matching!\n");
		return 1;
	}


	return 0;
}


struct tokenArray *initTokenArray(char *re)
{
	//this function will initialize and build list array according to RE size
	// storing the length of the regular expression
  struct tokenArray *arr;
	arr=(struct tokenArray*)malloc(sizeof(struct tokenArray));

	int len = strlen(re);
	int i,top =-1;
	// variable to store no.of tokens
	int Count =0;
	// counting the no.of tokens in the regular expression
	for(i=0;i<(len-1);i++)
	{
		// Taking an expression enclosed in () or ()* or ()|() or ()|a paranthesis as a single token

		if(re[i] == '(')
		{
			Count++;
			top++;
			// Taking the first expression within ()
			while(top!=-1)
			{
				i++;
				if(re[i]=='(')
					top++;
				if(re[i]==')')
					top--;
			}
			// Taking  a single token as ()*
			if(re[i+1]=='*')
				i++;
			// taking a single Token as ()|() or ()|a
			else if(re[i+1] == '|')
			{
				i++;
				if(isalpha(re[i+1]))
					i++;
				else if(re[i+1]=='(')
				{
					i=i+1;
					top++;
					while(top!=-1)
					{
						i++;
						if(re[i]=='(')
							top++;
						if(re[i]==')')
							top--;
					}

				}


			}
		}
		// Taking a symbol with unary operator  t*
		else if(isalpha(re[i]) && re[i+1]=='*')
		{
			Count++;
			i++;
		}
		// Taking two symbols with binary operator "|" as a single token (i.e. a|b)
		else if(isalpha(re[i])&&re[i+1]=='|' && isalpha(re[i+2]))
		{
			Count++;
			i=i+2;
		}
		// Taking a single token as a|()
		else if(isalpha(re[i])&&re[i+1]=='|' && re[i+2] == '(')
		{
			Count++;
			i=i+2;
			top++;
			// Taking the first expression within ()
			while(top!=-1)
			{
				i++;
				if(re[i]=='(')
					top++;
				if(re[i]==')')
					top--;
			}

		}

		// Taking each symbol as individual token
		else
		{
				Count++;

		}
	}
		// An extra count for augmentation '#'
		Count++;
		// Allocating the No.of Tokens
		arr->tokenCount = Count;
		// Allocating a memory for tokens
		arr->list =(struct tokenNode*)malloc(Count * sizeof(struct tokenNode));
		return arr;
}

struct tokenArray *parseAndStoreTokens(char *re)
{
	//this function will parse tokens and store them in tokenArray

	// Initialize the tokenArray;
	struct tokenArray *arr;
	arr = initTokenArray(re);
	int len=strlen(re);
	int i,top=-1;
	int Count = 0;
	//Parse a single token as a content with in () or ()* or ()|() or ()|a


	for(i=0;i<(len-1);i++)
	{
		// Parse a single token whose 1st Little Array is ()
		if(re[i] == '(')
		{
			arr->list[Count].symbol1 = '\0';
			char buffer[MAX];
			int ind =-1;
			top++;
			// parsing the contents within the paranthesis
			while(top!=-1)
			{
				i++;
				buffer[++ind]=re[i];
				if(re[i]=='(')
					top++;
				if(re[i]==')')
					top--;
			}

			buffer[ind]='\0';
			// Recursuive call
			arr->list[Count].littleArray1 = parseAndStoreTokens(buffer);
			// Reset Buffer
			bzero((void *)buffer,ind);
			ind = -1;
			// Enter the Unary operator *
			if(re[i+1]=='*')
			{
				i++;
				arr->list[Count].op = re[i];
			}
			// For the Binary operator *
			else if(re[i+1] == '|')
			{
				i++;
				// Setting the operator
				arr->list[Count].op = re[i];
				if(re[i+1]=='(')
				{
					i++;
					// Parsing the token for2nd LittleArray
					while(top!=-1)
					{
						i++;
						buffer[++ind]=re[i];
						if(re[i]=='(')
							top++;
						if(re[i]==')')
							top--;
					}
					buffer[ind]='\0';
					// Reccursive call
					arr->list[Count].littleArray2 = parseAndStoreTokens(buffer);
					arr->list[Count].symbol2 = '\0';
					//reset the buffer
					bzero((void *)buffer,ind);
					ind =-1;
				}
				// parsing the token as ()|a
				else
				{
					i++;
					arr->list[Count].symbol2=re[i];
					arr->list[Count].littleArray2 = NULL;
				}
					// Increase the token Node Count

			}
			else
			{
				arr->list[Count].littleArray2 = NULL;
				arr->list[Count].symbol2 = '\0';
				arr->list[Count].op = '\0';
			}
			// Increase the token Node Count

			Count ++;

		}

		//Parse a single token as a content with a|() or a* or a|b or a
		else if (isalpha(re[i]))
		{
			char *buffer;
			int ind =-1;
			arr->list[Count].littleArray1 = NULL;
			arr->list[Count].symbol1 = re[i];
			// taking token as Single a
			if(isalpha(re[i+1]))
			{

				arr->list[Count].littleArray2 = NULL;
				arr->list[Count].symbol2 = '\0';
				arr->list[Count].op = '\0';
			}
			// setting the unary operator *
			else if (re[i+1] = '*')
			{
				i++;
				arr->list[Count].op = re[i];
				arr->list[Count].littleArray2 = NULL;
				arr->list[Count].symbol2 = '\0';
			}
			// setting the binary operator ' | '
			else if (re[i+1]='|')
			{
				i++;
				arr->list[Count].op = re[i];
				// taking a single token as a|b
				if(isalpha(re[i+1]))
				{
					i++;
					arr->list[Count].littleArray2 = NULL;
					arr->list[Count].symbol2 = re[i];
				}
				// taking a single token as a|()
				else if(re[i+1]='(')
				{
					i++;
					// Parsing the token for2nd LittleArray
					while(top!=-1)
					{
						i++;
						buffer[++ind]=re[i];
						if(re[i]=='(')
							top++;
						if(re[i]==')')
							top--;
					}
					buffer[ind]='\0';
					// Reccursive call
					arr->list[Count].littleArray2 = parseAndStoreTokens(buffer);
					arr->list[Count].symbol2 = '\0';
					//reset the buffer
					bzero((void *)buffer,ind);
					ind =-1;

				}
			}

		}

	}

	return arr;

}


void printTokenArray(struct tokenArray *arr)
{
	if(arr==NULL||arr->tokenCount==0||arr->list==NULL)
		return;

	int i;
	printf("\n");
	for(i=0;i<arr->tokenCount;i++)
	{
		printf("\n");
		printf("Symbol 1: %c\n",arr->list[i].symbol1);
		printf("Operator: %c\n",arr->list[i].op);
		printf("Symbol 2: %c\n",arr->list[i].symbol2);
		if(arr->list[i].littleArray1!=NULL)
			printf("little arr1 present\n");
		if(arr->list[i].littleArray2!=NULL)
			printf("little arr2 present\n");

		printTokenArray(arr->list[i].littleArray1);
		printTokenArray(arr->list[i].littleArray2);
	}
}

int main()
{
	char REstring[MAX];
	printf("\nEnter RE: ");
	scanf("%[^\n]",REstring);

	printf("The RE entered:\n'%s'\n",REstring);

	struct tokenArray *MainTokenArray=NULL;

	if(normalizeRE(REstring))
	{
		printf("\nWrong Regular Expression!");
		return 0;
	}

	printf("The normalized RE:\n'%s'\n",REstring);

	MainTokenArray = parseAndStoreTokens(REstring);

	printf("\nThe tokenised array:\n");
	printTokenArray(MainTokenArray);

	return 0;
}
