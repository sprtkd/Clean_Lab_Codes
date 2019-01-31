//binary search tree
#include<stdio.h>
#include<stdlib.h>

typedef struct Tree
{
	struct Tree *LC,*RC;
	int data;
}BST;


void insertTree(BST **R,int v)
{
	if(*R==NULL)
	{
		*R=(BST*)malloc(sizeof(BST));
		(*R)->data = v;
		(*R)->LC = NULL;
		(*R)->RC = NULL;
	}
	else if((*R)->data > v)
		insertTree(&((*R)->LC ),v);
	else if((*R)->data > v)
		insertTree(&((*R)->RC ),v);
	else
		printf("\nDuplicate Data!!");
}



int main()
{
	BST *Root=NULL;
	int opt,val;
	
	opt=1;
	printf("\nEnter \n\t1 to insert\n\t2 to delete node with only child"
	"\n\t3 to delete node with both children\n\t4 to display"
	"\n\t5 to find an element\n\t6 to find min\n\t7 to find max"
	"\n\t8 to print left child of given node\n\t9 to print right child of a given node"
	"\n\t10 to print info about tree\n\t0 to exit...");
	while (opt)
	{
		printf("\nEnter option:");
		scanf("%d",&opt);

		switch(opt)
		{
			case 1:printf("\nEnter value to store:");
					scanf("%d",&val);
					insertTree(&Root,val);
					break;
					
			case 2:
					break;
			case 3:
					break;
			case 4:
					break;
			case 5:
					break;
			case 6:
					break;
					
			case 7:
					break;
					
			case 8:
					break;
			case 9:
					break;
			case 10:
					break;
			case 0:printf("\nExiting...");
					break;
			default:printf("\nInvalid option!!!");
					break;

	}
}
	return 0;
	
}
