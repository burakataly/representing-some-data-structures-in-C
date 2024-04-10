#include<stdio.h>
#include<stdlib.h>

/*
create fonksiyonunda graph yaratýrken node'larý adjacency list þeklinde tutuyoruz. adjacency list, bir array of pointers. Yani her bir elemaný
bir node'un adresini tutuyor. Node'larý [0-n-1] aralýðýnda isimlendirdiðimizi düþün. Bu yüzden adjList'teki her bir index o index'li node'un
komþularýný tutacak. Yani her bir index bir linkedlist aslýnda.

Her edge oluþturduðumuzda belirtilen etiketteki node'larý sýfýrdan yaratýp adjList'in o etiketlerdeki linkedlistlerine ekliycez. Ekleme iþini
pushFront yani baþa eleman ekleme olarak yapýcaz. Mesela src'den dest'e bir edge eklemek için önce dest etiketli bir node oluþturup sonra bu
node'un next'ine adjList[src]'yi atýycaz. Çünkü adjList[src]'de src etiketli node'un komþularýnýn linkli listesi var ve adjList[src] bu linkli
listenin head görevini görüyor. Ben dediðim atamayý yapýnca yeni dest etiketli node'un head'in iþaret ettiði node'a iþaret etmesin saðladým.
Sonrasýnda adjList[src]'ye dest etiketli yeni yarattýðým node'un adresini atarsam head, yani adjList[src], artýk dest'in adresini tutuyor olur.

Bu bir undirected graph olduðu için ayný þeyi adjList[dest] için de yapýyoruz. directed olsaydý birisi yeterli olacaktý. 

Yani gördüðün gibi n tane node yaratýp bunlarýn arasýnda baðlantý kurmuyoruz. Bir node'a eklenen her bir node için o node'dan tekrar yaratýyoruz.
Mesela addEdge(0,3) ve addEdge(2,3) çaðrýlarý yapýlsa iki tane 3 etiketli node yaratmýþ oluruz.
*/

//vertex: node'un etiketi / indexi
struct node{
	int vertex;
	struct node* next;
};

typedef struct node NODE;

struct graph{
	int numOfNodes;
	NODE** adjList;
};

typedef struct graph GRAPH;

NODE* createNode(int);
GRAPH* createGraph(int);
void addEdges(GRAPH*, int, int);
int hasEdge(GRAPH*, int, int);
void removeEdges(GRAPH*, int, int);
void printAdjList(GRAPH*);

int main(){
	int n = 4;
	GRAPH* graph = createGraph(n);
	addEdges(graph, 0, 4); // return olur, 4 etiketli node yok.
	addEdges(graph, 0, 1);
	addEdges(graph, 0, 3);
	addEdges(graph, 0, 2);
	addEdges(graph, 1, 2);
	addEdges(graph, 2, 3);
	addEdges(graph, 2, 3); // return olur, zaten eklenmiþti.
	
	removeEdges(graph, 2, 3);
	//removeEdges(graph, 4, 0, 1);
	
	printAdjList(graph);
	
	return 0;
}

NODE* createNode(int vertex){
	NODE* node = (NODE*) malloc(sizeof(NODE));
	node -> vertex = vertex;
	node -> next = NULL;
	return node;
}

GRAPH* createGraph(int n){
	int i;
	GRAPH* graph = (GRAPH*) malloc(sizeof(GRAPH));
	graph -> numOfNodes = n;
	graph -> adjList = (NODE**) calloc(n, sizeof(NODE*));
	return graph;
}

void addEdges(GRAPH* graph, int src, int dest){
	if(src == dest || src >= graph -> numOfNodes || dest >= graph -> numOfNodes) return;
	if(hasEdge(graph, src, dest)) return;
	
	// Add edge from src to dest
	NODE* newNode = createNode(dest);
	newNode->next = graph->adjList[src];
	graph->adjList[src] = newNode;
	
	// Add edge from dest to src
	newNode = createNode(src);
	newNode->next = graph->adjList[dest];
	graph->adjList[dest] = newNode;
}

int hasEdge(GRAPH* graph, int src, int dest){
	NODE* temp = graph -> adjList[src];
	while(temp != NULL){
		if(temp -> vertex == dest) return 1;
		temp = temp -> next;
	}
	return 0;
}

void removeEdges(GRAPH* graph, int src, int dest){
	if(src == dest || src >= graph -> numOfNodes || dest >= graph -> numOfNodes) return;
	
	NODE* temp = graph -> adjList[src];
	if(temp == NULL) return;
	if(temp -> vertex == dest){
		graph -> adjList[src] = temp -> next;
		free(temp);
	}
	else{
		while(temp -> next != NULL && temp -> next -> vertex != dest){
			temp = temp -> next;
		}
		if(temp -> next != NULL){
			NODE* temp2 = temp -> next;
			temp -> next = temp2 -> next;
			free(temp2);
		}
	}
	temp = graph -> adjList[dest];
	if(temp -> vertex == src){
		graph -> adjList[dest] = temp -> next;
		free(temp);
	}
	else{
		while(temp -> next != NULL && temp -> next -> vertex != src){
			temp = temp -> next;
		}
		if(temp -> next != NULL){
			NODE* temp2 = temp -> next;
			temp -> next = temp2 -> next;
			free(temp2);
		}
	}
}

void printAdjList(GRAPH* graph){
	int i, n = graph -> numOfNodes;
	for(i=0; i<n; i++) {
	    printf("%d -> ", i); // hangi node'un komþularý.
	    NODE* temp = graph -> adjList[i];
	    while(temp != NULL) {
	        printf("%d, ", temp -> vertex);
	        temp = temp -> next;
	    }
	    printf("\n");
	}
}
