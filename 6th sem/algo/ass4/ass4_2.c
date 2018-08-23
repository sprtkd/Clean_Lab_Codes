//Graph connected components
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

void DFS(int v, int *visited, struct graph *g)
{
	visited[v]=1;
	printf("V%d ",v+1);
	
	int i;
	
	for(i=0;i<g->Vcount;i++)
	{
		if(visited[i]==0 && g->adjMat[v][i]!=0)
			DFS(i, visited, g);
	}
}

void printConnectedComponents(struct graph *g)
{
	int v;
	int visited[g->Vcount];
	
    for(v = 0; v < g->Vcount; v++)
        visited[v] = 0;
 	
 	printf("\nThe connected components are:\n\n");
 	
    for (v=0; v<g->Vcount; v++)
    {
        if (visited[v] == 0)
        {
            DFS(v, visited, g);
            printf("\n");
        }
    }
}

int main()
{
	struct graph G;
	int S,D;
	
	//fill graph
    fillGraph(&G);
    printGraph(&G);
    
    //print connected components
    printConnectedComponents(&G);
    return 0;
}
