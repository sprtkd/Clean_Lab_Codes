//Graph shortest path using djikstra's
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#define MAX 100

struct graph
{
	int Vcount;
	int Ecount;
	int adjMat[MAX][MAX];
};

struct dnode
{
	int visited;
	int cost;
	int prevVertex;
};

void fillGraph(struct graph *g)
{
	int i,j;
	printf("\nEnter the number of vertices: ");
	scanf("%d",&(g->Vcount));
	g->Ecount=0;
	printf("\nEnter costs: (<0 for no connection)");
	for(i=0;i<g->Vcount;i++)
	{
		for(j=0;j<g->Vcount;j++)
		{
			printf("\nCost of connection V%d to V%d: ",i+1,j+1);
			scanf("%d",&(g->adjMat[i][j]));
			if((g->adjMat[i][j])>0)
				(g->Ecount)++;							
		}
	}
}

void printGraph(struct graph *g)
{
	int i,j;
	printf("\nDirected Graph\n");
	printf("\nVertices: %d",g->Vcount);
	printf("\nEdges: %d",g->Ecount);
	
	printf("\nAdjacency Matrix:\n");
	
	for(i=0;i<g->Vcount;i++)
	{
		printf("\tV%d",i+1);
	}
	
	for(i=0;i<g->Vcount;i++)
	{
		printf("\nV%d",i+1);
		for(j=0;j<g->Vcount;j++)
		{
			printf("\t%d",(g->adjMat[i][j]));
		}
	}
}

int MinUnvisited(struct dnode *dl, int n)
{
	int minPos=-1, minCost=INT_MAX, i;
	
	for(i=0;i<n;i++)
	{
		if(dl[i].cost<minCost && dl[i].visited==0)
		{
			minCost=dl[i].cost;
			minPos = i;
		}
	}
	
	if(minPos>=0)
		return minPos;
	else
		return -1;//return <0 if no unvisited
}

void DjikstraShortestPath(struct graph *g,struct dnode *dl, int S,int D)
{
	if(S>g->Vcount || D>g->Vcount)
	{
		printf("Source/Destination out of bounds!\n");
		exit(0);
	}
	
	int i, l=1, curr_v, curr_cost;
	
	//offsetting to 0 start
	S--;
	D--;
	
	//initialize the list
	for(i=0;i<g->Vcount;i++)
	{
		dl[i].visited=0;
		dl[i].cost = INT_MAX;
		dl[i].prevVertex=-1;
	}
	dl[S].cost=0;
	
	while(1)
	{
		//check if all are visited, if all are visited break
		curr_v = MinUnvisited(dl, g->Vcount);//current vertex = minimum cost from start vertex unvisited
		if(curr_v<0)
			break;
		
		
		//see all neighbouring vertices of current vertex
		for(i=0;i<g->Vcount;i++)
		{
			if(g->adjMat[curr_v][i]>0)
			{
				curr_cost = dl[curr_v].cost + g->adjMat[curr_v][i];
				
				if(curr_cost < dl[i].cost)
				{
					dl[i].cost = curr_cost;
					dl[i].prevVertex = curr_v;
				}
			}
		}
		
		dl[curr_v].visited=1;
	}
	
	printf("\nList:\n");
	for(i=0;i<g->Vcount;i++)
	{
		printf("V%d: visited:%d cost:%d prev:%d\n",i+1,dl[i].visited, dl[i].cost,(dl[i].prevVertex)+1);
	}
}

void printShortestPath(struct dnode *dl, int S,int D)
{
	S--;
	D--;
	
	int curr_v=D;
	
	if(dl[curr_v].cost==INT_MAX)
	{
		printf("\nPath does not exist!\n");
		return;
	}
	else
		printf("\nCost: %d\n",dl[curr_v].cost);
	
	printf("\nPath:\n\nV%d ",curr_v+1);
	while(1)
	{
		curr_v = dl[curr_v].prevVertex;
		printf("<-V%d ",curr_v+1);
		if(curr_v==S)
			break;
	}
	printf("\n");
}

int main()
{
	struct graph G;
	struct dnode dlist[MAX];
	int S,D;
	
	//fill graph
    fillGraph(&G);
    printGraph(&G);
    
    //take input
    printf("\nEnter path source: ");
    scanf("%d",&S);
    printf("\nEnter path destination: ");
    scanf("%d",&D);
    
    //find path
    DjikstraShortestPath(&G,dlist,S,D);
    printShortestPath(dlist,S,D);
    return 0;
}
