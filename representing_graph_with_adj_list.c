#include<stdio.h>
#include<stdlib.h>


//vertex: label of the node
typedef struct node{
	int vertex;
	struct node* next;
}NODE;

typedef struct diGraph{
	int numOfNodes;
	NODE** adjList;
}DiGRAPH;

NODE* createNode(int);
DiGRAPH* createDiGraph(int);
void addEdges(DiGRAPH*, int, int);
int hasEdge(DiGRAPH*, int, int);
void printAdjList(DiGRAPH*);

int main(){
	int n = 4;
	DiGRAPH* diGraph = createDiGraph(n);
	addEdges(diGraph, 0, 4); // return olur, 4 etiketli node yok.
	addEdges(diGraph, 0, 1);
	addEdges(diGraph, 0, 3);
	addEdges(diGraph, 0, 2);
	addEdges(diGraph, 1, 2);
	addEdges(diGraph, 2, 3);
	addEdges(diGraph, 2, 3); // return olur, zaten eklenmiþti.
	
	printAdjList(diGraph);
	
	return 0;
}

NODE* createNode(int vertex){
	NODE* node = (NODE*) malloc(sizeof(NODE));
	node -> vertex = vertex;
	node -> next = NULL;
	return node;
}

DiGRAPH* createDiGraph(int n){
	int i;
	DiGRAPH* diGraph = (DiGRAPH*) malloc(sizeof(DiGRAPH));
	diGraph -> numOfNodes = n;
	diGraph -> adjList = (NODE**) calloc(n, sizeof(NODE*));
	return diGraph;
}

void addEdges(DiGRAPH* diGraph, int src, int dest){
	if(src == dest || src >= diGraph->numOfNodes || dest >= diGraph->numOfNodes) return;
	if(hasEdge(diGraph, src, dest)) return;
	
	//adding edge from src to dest
	NODE* newNode = createNode(dest);
	newNode->next = diGraph->adjList[src];
	diGraph->adjList[src] = newNode;
	
	//adding edge from dest to src
	newNode = createNode(src);
	newNode->next = diGraph->adjList[dest];
	diGraph->adjList[dest] = newNode;
}

int hasEdge(DiGRAPH* diGraph, int src, int dest){
	NODE* temp = diGraph -> adjList[src];
	while(temp != NULL){
		if(temp -> vertex == dest) return 1;
		temp = temp -> next;
	}
	return 0;
}

void printAdjList(DiGRAPH* diGraph){
	int i;
	for(i=0; i<diGraph->numOfNodes; i++) {
	    printf("%d -> ", i);
	    NODE* temp = diGraph -> adjList[i];
	    while(temp != NULL) {
	        printf("%d, ", temp -> vertex);
	        temp = temp -> next;
	    }
	    printf("\n");
	}
}
