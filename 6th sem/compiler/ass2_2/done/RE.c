#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 10000

//tokenise=============================================================================================================
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

// MAthematical tools +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

// function to perform Union operation

int *Union(int a1[],int a2[],int n,int n1,int n2)
{
	int i,k=0;
	int *a = (int *)malloc((n+1)*sizeof(int));
	memset((void *)a, 0, (n+1));
	for(i=0;i<n1;i++)
	{
		k=a1[i];
		a[k]=1;
		
	}
	for(i=0;i<n2;i++)
	{
		k=a2[i];
		a[k]=1;
	}
	return a;
}


// insert a charachter at particular position in a string
void charins(char *S,char c,int n)
{
	int len = strlen(S);
	int i;
	for(i = len;i>n;i--)
	{
		S[i]=S[i-1];
	}
	S[n]=c;
	S[len+1]='\0';
}

// Mathematical tools ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// function to normalize the given input RE and verify it
int normalizeRE(char *re)
{
	//this will cleanup re and remove stray spaces and extra characters
	//and any error in re return 1;
	int i,j,len,l, top;
	char brackets[MAX];
	/*proper bracketting of the regular expression for the following cases :
		case 1 : a* | b* ==> (a*)|(b*)
		case 2 * (abb)*|(abc)* ===> ((abb)*)|((abc)*)	*/
	
	l = strlen(re);
	i=0;
	while(re[i]!='\0')
	{

		// case : a*|....
		if(isalpha(re[i])&&(re[i+1]=='*')&&(re[i+2] == '|'))
			{
				charins(re,'(',i);
				charins(re,')',i+3);
				i = i+4;
			}
		// case : ... | b*
		if(re[i]=='|' && (isalpha(re[i+1])) && (re[i+2] =='*'))
			{
				charins(re,'(',i+1);
				charins(re,')',i+4);
				i=i+4;
			}
		// case : ... ()*|b
		if(re[i]==')' && re[i+1]=='*' && re[i+2] == '|')
			{
				charins(re,')',i+2);
				int j=i;
				int top = 0;
				while(top !=-1)
				{
					j--;
					if(re[j]==')')
						top++;
					if(re[j] == '(')
						top--;
				}
				charins(re,'(',j);
				i=i+4;				
			}
		//case : ....a|()*
		if(re[i]=='|' && re[i+1]=='(' )
		{
			int z = i;
			int k =i;
			k++;
			int top=0;
			while(top != -1)
			{
				k++;
				if(re[k]=='(')
					top++;
				if(re[k]==')')
					top--;
			}
			if(re[k+1]=='*')
				{
					charins(re,')',k+2);
					charins(re,'(',z+1);
					i=k+2;
				}
			
		}
		
		i++;
	}


	len =strlen(re);

	//enter # to mark end
	//augmented RE
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

		if(!(re[i]=='*'||re[i]=='|'||re[i]==' '||re[i]=='+'||re[i]=='('||re[i]==')'||isalpha(re[i])||re[i]=='#'))
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

int countSymbols(char *re)
{
	int n=strlen(re),i,c=0;

	for(i=0;i<n;i++)
	{
		if(isalpha(re[i])||re[i]=='#')
			c++;
	}
	return c;
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
	for(i=0;i<(len);i++)
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
		printf("\n %d \n",Count);
		// Allocating the No.of Tokens
		arr->tokenCount = Count;
		// Allocating a memory for tokens
		arr->list =(struct tokenNode*)malloc((Count) * sizeof(struct tokenNode));
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

	for(i=0;i<(len);i++)
	{
		// Parse a single token whose 1st Little Array is ()
		if(re[i] == '(')
		{
			arr->list[Count].symbol1 = '\0';
			char buffer[MAX];
			char buffer2[MAX];
			int ind =-1;
			int ind2 =-1;
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
			top=-1;
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
					top++;
					// Parsing the token for 2nd LittleArray
					while(top!=-1)
					{
						i++;
						buffer2[++ind2]=re[i];
						if(re[i]=='(')
							top++;
						if(re[i]==')')
							top--;
					}
					buffer2[ind2]='\0';
					// Reccursive call
					arr->list[Count].littleArray2 = parseAndStoreTokens(buffer2);
					arr->list[Count].symbol2 = '\0';
					//reset the buffer
					bzero((void *)buffer2,ind2);
					ind2 =-1;
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
			Count++;
		}

		//Parse a single token as a content with a|() or a* or a|b or a
		else if (isalpha(re[i]))
		{
			char buffer[MAX];
			int ind =-1;
			arr->list[Count].littleArray1 = NULL;
			arr->list[Count].symbol1 = re[i];
			// taking token as Single a
			if(isalpha(re[i+1])||re[i+1]=='#')
			{
				arr->list[Count].littleArray2 = NULL;
				arr->list[Count].symbol2 = '\0';
				arr->list[Count].op = '\0';
			}
			// setting the unary operator *
			else if (re[i+1] == '*')
			{
				i++;
				arr->list[Count].op = re[i];
				arr->list[Count].littleArray2 = NULL;
				arr->list[Count].symbol2 = '\0';
			}
			// setting the binary operator ' | '
			else if (re[i+1]=='|')
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
				else if(re[i+1]=='(')
				{
					i++;
					top++;
					// Parsing the token for 2nd LittleArray
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
			//Increase the Token Node Count
			Count++;
		}
		else if(re[i]=='#')
		{
			arr->list[Count].symbol1 = re[i];
			arr->list[Count].littleArray1 = NULL;
			arr->list[Count].op = '\0';
			arr->list[Count].littleArray2 = NULL;
			arr->list[Count].symbol2 = '\0';
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
	printf("\n No.of.Tokens :\t%d\n\n ",arr->tokenCount);
	for(i=0;i<arr->tokenCount;i++)
	{
		printf("\n");
		printf("Symbol 1: %c\n",arr->list[i].symbol1);
		printf("Operator: %c\n",arr->list[i].op);
		printf("Symbol 2: %c\n",arr->list[i].symbol2);
		if(arr->list[i].littleArray1!=NULL)
		{
			printf("little arr1 present\n");
			printf("\n  ****************************\n");
			printTokenArray(arr->list[i].littleArray1);
			printf("\n  ****************************\n");
		}
		if(arr->list[i].littleArray2!=NULL)
		{
			printf("little arr2 present\n");
			printf("\n ****************************\n");
			printTokenArray(arr->list[i].littleArray2);
			printf("\n ****************************\n");
		}
	printf("\n-------------------------------------\n");
	}
}

//tokenise=============================================================================================================




//syntax tree===========================================================================================================
struct posarray
{
	int poscount;
	int *poslist;

	//this data structure will store firstpos and lastpos
};

struct syntaxNode
{
	char data;
	int nullable;
	struct posarray firstpos;
	struct posarray lastpos;
	struct syntaxNode *leftchild;
	struct syntaxNode *rightchild;

	//for building syntax tree
};


struct syntaxNode *createSyntaxNode(char ch, int s_curr, int s_count)
{
	//build the node and return the node's address

	struct syntaxNode *newNode;
	newNode = (struct syntaxNode *)malloc(sizeof(struct syntaxNode));

	newNode->data = ch;
	newNode->nullable = 0;
	newNode->leftchild = NULL;
	newNode->rightchild = NULL;

	newNode->firstpos.poscount=0;
	newNode->firstpos.poslist = (int*)malloc(s_count*sizeof(int));

	newNode->lastpos.poscount=0;
	newNode->lastpos.poslist = (int*)malloc(s_count*sizeof(int));

	//support for epsilon
	if(ch=='e')
	{
		return newNode;
	}
	//if s_curr!=0, store pos s
	if(s_curr!=0)
	{
		newNode->firstpos.poslist[0] = s_curr;
		newNode->firstpos.poscount=1;

		newNode->lastpos.poslist[0] = s_curr;
		newNode->lastpos.poscount=1;
	}
	return newNode;

}

struct syntaxNode *Token2syntaxNode(struct tokenNode *token_n, int *flag, int *s_curr, int s_count)
{

	//flag: return 0 if no littlearray, 1 if littlearray 1, 2 if both, 3 if only littleArray2

	//take a new empty pointer
	struct syntaxNode *newNodePtr=NULL, *temp;
	*flag = 0;
	//cases:

	if(token_n->op=='*')
	{
		// * is present, build a node with star and store in new
		newNodePtr = createSyntaxNode('*', 0, s_count);
	}
	else if(token_n->op=='|')
	{
		// | is present,  build a node with pipe and store it in new
		newNodePtr = createSyntaxNode('|', 0, s_count);
	}


	// symbol1 present, increment s_curr, build a node and put char, tell to store pos s, if new is empty store there, else in new->leftchild
	if(token_n->symbol1!='\0')
	{
		(*s_curr)++;
		temp = createSyntaxNode(token_n->symbol1, *s_curr, s_count);
		if(newNodePtr==NULL)
			newNodePtr = temp;
		else
			newNodePtr->leftchild = temp;
	}

	// symbol2 present, increment s_curr, build a node and put char, tell to store pos s, and store in new->rightchild
	if(token_n->symbol2!='\0')
	{
		(*s_curr)++;
		temp = createSyntaxNode(token_n->symbol2, *s_curr, s_count);
		newNodePtr->rightchild = temp;
	}

	if(token_n->littleArray1==NULL && token_n->littleArray2==NULL)//littlearrays not present, flag=0
		*flag = 0;
	else if(token_n->littleArray1!=NULL && token_n->littleArray2==NULL)//littleArray1 present only, flag=1
		*flag = 1;
	else if(token_n->littleArray1!=NULL && token_n->littleArray2!=NULL)//littleArray1 present && littleArray2 present, flag=2
		*flag = 2;
	else if(token_n->littleArray1==NULL && token_n->littleArray2==NULL)//littleArray2 present only, flag=3
		*flag = 3;

	//return new
	return newNodePtr;
}

struct syntaxNode *syntaxTreeBuilder(struct tokenArray *tokenarr, int *s_curr, int s_count)
{
	struct syntaxNode *synRoot=NULL, *synNew, *temp;
	int i, flag;

	//special handling for first token
	//take a node, store it in root
	synRoot = Token2syntaxNode(&(tokenarr->list[0]),&flag,s_curr,s_count);

	//if flag=1||2, call recursive littlearray1 and store it
	if(flag==1||flag==2)
	{
		temp = syntaxTreeBuilder((tokenarr->list[0]).littleArray1, s_curr,s_count);
		//if root is still NULL, store it there only,
		if(synRoot == NULL)
		{
			synRoot = temp;
		}
		else
		{
			//otherwise store it in root->leftchild
			synRoot->leftchild = temp;
		}
	}
	
	if(flag==2||flag==3)
	{	
		//if flag=2||3, call recursive littleArray2 and store it in root->rightchild
		temp = syntaxTreeBuilder((tokenarr->list[0]).littleArray2, s_curr,s_count);
		synRoot->rightchild = temp;
	}

	
	//mini tree building loop
	for(i = 1; i < (tokenarr->tokenCount); i++)
	{
		//create a cat node and store it in new ptr
		synNew = createSyntaxNode('.', 0, s_count);
		
		//leftchild
		//store root in new->leftchild
		synNew->leftchild = synRoot;
		//store new in root, new root is created
		synRoot = synNew;
		
		//rightchild
		//take a node, store it in root->rightchild
		synRoot->rightchild = Token2syntaxNode(&(tokenarr->list[i]),&flag,s_curr,s_count);
		
		//if flag=1||2, call recursive littlearray1 and store it
		if(flag==1||flag==2)
		{
			temp = syntaxTreeBuilder((tokenarr->list[i]).littleArray1, s_curr,s_count);
			//if Root->rightchild is still NULL, store it there only,
			if(synRoot->rightchild == NULL)
			{
				synRoot->rightchild = temp;
			}
			else
			{
				//otherwise store it in root->rightchild->leftchild
				synRoot->rightchild->leftchild = temp;
			}
		}
	
		if(flag==2||flag==3)
		{	
			//if flag=2||3, call recursive littleArray2 and store it in root->rightchild->rightchild
			temp = syntaxTreeBuilder((tokenarr->list[i]).littleArray2, s_curr,s_count);
			synRoot->rightchild->rightchild = temp;
		}
		
	}

	//return final root
	return synRoot;
}


// nullable ============================================================================================================
// function to check where the node is nullable or not
void isnullable(struct syntaxNode *node)
{
	// true if node labelled epsilon
	if(node->data == 'e')
		{
			node->nullable = 1;
		}
	// true if a node labelled *	
	else if(node->data == '*')
		{
			node->nullable = 1;
		}
	// for a node labelled c1.c2 nulable(c1)and nullable(c2)	
	else if(node->data == '.')
		{
			node->nullable = (node->leftchild->nullable)&&(node->rightchild->nullable);
		}
	// for a node labelled c1|c2 nulable(c1) or nullable(c2)	
	else if(node->data == '|')
		{
			node->nullable = ((node->leftchild->nullable)||(node->rightchild->nullable));
		}
	// for a node labelled  with i not nullable	
	else 
		{
			node->nullable = 0;
		}
}

// To set the nullable of each node
// tree is being parsed in LVR manner
void nullable (struct syntaxNode *synRoot)
{
	if(synRoot == NULL)
		return;
	//L
	nullable(synRoot->leftchild);
	//V
	nullable(synRoot->rightchild);
	//R
	isnullable(synRoot);
	
}// end of Nullable
//nullable ==============================================================================================================

//FIRSTPOS and LASTPOS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FLpos(struct syntaxNode *node,int s_count)
{

	int i=0;
	// FIRSTPOS is NULL if node labelled 'e' and if leaf labeled with position i then  firstpos =i and lastpos =i
	// Already implented during syntax tree creation.

	// if a node labelled '|' ; fisrtpos is fp(c1) U fp(c2) ; lastpos is lp(c1) U lp(c2) 	
	if(node->data == '|')
		{
			int *fp = Union(node->leftchild->firstpos.poslist,node->rightchild->firstpos.poslist,s_count,node->leftchild->firstpos.poscount,node->rightchild->firstpos.poscount);
			int *lp = Union(node->leftchild->lastpos.poslist,node->rightchild->lastpos.poslist,s_count,node->leftchild->lastpos.poscount,node->rightchild->lastpos.poscount);
			for(i=0;i<s_count;i++)
			{
				if(fp[i] == 1)
					node->firstpos.poslist[node->firstpos.poscount++]=(i);
				if(lp[i] == 1)
					node->lastpos.poslist[node->firstpos.poscount++] =(i);
			}
			
		}
	// if a node labelled '*' ; firstpos id fp(c1) ; lastpos is lp(c1)
	else if(node->data == '*')
	{
		for(i=0;i<node->leftchild->firstpos.poscount;i++)
		{
			node->firstpos.poslist[node->firstpos.poscount++]=node->leftchild->firstpos.poslist[i];
		}
		for(i=0;i<node->leftchild->lastpos.poscount;i++)
		{
			node->lastpos.poslist[node->lastpos.poscount++]=node->leftchild->lastpos.poslist[i];
		}
	}
	
	// if a node labelled '.' 
	// FIRSTPOS;
	/*	if (nullable(c1))
			firstpos = fp(c1) U fp(c2)
		else
			firstpos = fp(c1)
	*/
	// LASTPOS;
	/*
		if(nullable(c2))
			lastpos = lp(c1) U lp(c2)
		else
			lastpos = lp(c2) 
	*/
	else if(node->data == '.')
	{
		if(node->leftchild->nullable)
		{
			int *fp = Union(node->leftchild->firstpos.poslist,node->rightchild->firstpos.poslist,s_count,node->leftchild->firstpos.poscount,node->rightchild->firstpos.poscount);
			for(i=0;i<s_count;i++)
			{
				if(fp[i] == 1)
					node->firstpos.poslist[node->firstpos.poscount++]=(i);
			}
		}
		else
		{
			for(i=0;i<node->leftchild->firstpos.poscount;i++)
			{
				node->firstpos.poslist[node->firstpos.poscount++]=node->leftchild->firstpos.poslist[i];
			}
			
		}
		if(node->rightchild->nullable)
		{
			int *lp = Union(node->leftchild->lastpos.poslist,node->rightchild->lastpos.poslist,s_count,node->leftchild->lastpos.poscount,node->rightchild->lastpos.poscount);
			for(i=0;i<s_count;i++)
			{
				if(lp[i] == 1)
					node->lastpos.poslist[node->lastpos.poscount++]=(i);
			}
			
		}
		else
		{
			for(i=0;i<node->rightchild->lastpos.poscount;i++)
			{
				node->lastpos.poslist[node->lastpos.poscount++]=node->rightchild->lastpos.poslist[i];
			}
			
		}
			
	}

}

// To set the firstpos and lastpos of each node
// tree is being parsed in LVR manner
void firstpos_lastpos(struct syntaxNode *synRoot,int s_count)
{
	if(synRoot == NULL)
		return;
	//L
	firstpos_lastpos(synRoot->leftchild,s_count);
	//V
	firstpos_lastpos(synRoot->rightchild,s_count);
	//R
	FLpos(synRoot,s_count);
}


//FIRSTPOS and LASTPOS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//function to print the syntax tree
void printSyntaxTree(struct syntaxNode *synRoot)
{
	int i;
	//print recursivly with vlr rule with addresses
	if(synRoot==NULL)
		return;
	printf("\n=================================\n");
	printf("\nAddress: %ld",(long int)(synRoot));
	printf("\nData: %c",synRoot->data);
	printf("\nNullable: %d",synRoot->nullable);
	printf("\nFirstpos Length: %d",synRoot->firstpos.poscount);
	printf("\nFirstpos: ");
	for(i=0;i<synRoot->firstpos.poscount;i++)
		printf("%d,",synRoot->firstpos.poslist[i]);
	printf("\nLastpos Length: %d",synRoot->lastpos.poscount);
	printf("\nLastpos: ");
	for(i=0;i<synRoot->lastpos.poscount;i++)
		printf("%d,",synRoot->firstpos.poslist[i]);	
	
	printf("\nLeft child: %ld",(long int)(synRoot->leftchild));
	printf("\nRight child: %ld",(long int)(synRoot->rightchild));
	
	printf("\n=================================\n");
	
	printSyntaxTree(synRoot->leftchild);
	printSyntaxTree(synRoot->rightchild);
	
	
}
//syntax tree===========================================================================================================
// Main Function
int main()
{
	char REstring[MAX];
	printf("\nSupported Characters: \n'a-d','f-z','A-Z',\n'e' for epsilon, '*','|','(',')'\n"); 
	printf("\n\tEnter RE: ");
	scanf("%[^\n]",REstring);
	printf("The RE entered:\n'%s'\n",REstring);

	struct tokenArray *MainTokenArray=NULL;
	int symbolcountcurr = 0,symbolcount;
        struct syntaxNode *syntaxRoot=NULL;

	if(normalizeRE(REstring))
	{
		printf("\nWrong Regular Expression! Program Terminated!\n");
		return 0;
	}
	printf("The normalized RE:\n'%s'\n",REstring);
	symbolcount = countSymbols(REstring);
	printf("The number of symbols is: %d\n",symbolcount);
	
	if(symbolcount<=1)
	{
		printf("\nRE empty!! Program Terminated!\n");
		return 0;
	}
	
	MainTokenArray = parseAndStoreTokens(REstring);
	printf("\nThe tokenised array:\n");
	printTokenArray(MainTokenArray);
	syntaxRoot = syntaxTreeBuilder(MainTokenArray,&symbolcountcurr,symbolcount);
	//nullable(syntaxRoot);
	//firstpos_lastpos(syntaxRoot,symbolcount);
	printSyntaxTree(syntaxRoot);

	return 0;
}//End of Main Function 
// End of Program
