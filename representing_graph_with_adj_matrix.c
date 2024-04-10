#include<stdio.h>
#include<stdlib.h>

// undirected graph için adjmatrix gösterimi. directed olsaydý edge ekleme ve silme iþleminde yalnýzca adjMatrix[src][dest]
// üzerinde iþlem yapardýn. 

int** createGraph(int);
void addEdge(int**, int, int, int);
void removeEdge(int**, int, int, int);
void printAdjMatrix(int**, int);

int main(){
	int n = 4;
	int** adjMatrix = createGraph(n);
	addEdge(adjMatrix, 4, 0, 4); // return olur, 4 etiketli node yok.
	addEdge(adjMatrix, 4, 0, 1);
	addEdge(adjMatrix, 4, 0, 3);
	addEdge(adjMatrix, 4, 0, 2);
	addEdge(adjMatrix, 4, 1, 2);
	addEdge(adjMatrix, 4, 2, 3);
	addEdge(adjMatrix, 4, 2, 3); // return olur, zaten eklenmiþti.
	removeEdge(adjMatrix, 4, 0, 1);
	printAdjMatrix(adjMatrix, n);
	
	return 0;
}

int** createGraph(int n){
	int i;
	int** adjMatrix = (int**) malloc(n*sizeof(int*));
	for(i=0;i<n;i++) adjMatrix[i] = (int*) calloc(n, sizeof(int));
	return adjMatrix;
}

void addEdge(int** adjMatrix, int n, int src, int dest){
	if(src == dest || src >= n || dest >= n) return;
	
	// Add edge from src to dest
	adjMatrix[src][dest] = 1;
	
	// Add edge from dest to src
	adjMatrix[dest][src] = 1;
}

void removeEdge(int** adjMatrix, int n, int src, int dest){
	if(src == dest || src >= n || dest >= n) return;
	
	// remove edge from src to dest
	adjMatrix[src][dest] = 0;
	
	// remove edge from dest to src
	adjMatrix[dest][src] = 0;
}

void printAdjMatrix(int** adjMatrix, int n){
	int i, j;
	for(i=0;i<n;i++) {
	    for(j=0;j<n;j++){
	    	printf("%d ", adjMatrix[i][j]);
		}
	    printf("\n");
	}
}
