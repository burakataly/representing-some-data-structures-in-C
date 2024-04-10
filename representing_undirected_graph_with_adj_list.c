#include<stdio.h>
#include<stdlib.h>

/*
create fonksiyonunda graph yarat�rken node'lar� adjacency list �eklinde tutuyoruz. adjacency list, bir array of pointers. Yani her bir eleman�
bir node'un adresini tutuyor. Node'lar� [0-n-1] aral���nda isimlendirdi�imizi d���n. Bu y�zden adjList'teki her bir index o index'li node'un
kom�ular�n� tutacak. Yani her bir index bir linkedlist asl�nda.

Her edge olu�turdu�umuzda belirtilen etiketteki node'lar� s�f�rdan yarat�p adjList'in o etiketlerdeki linkedlistlerine ekliycez. Ekleme i�ini
pushFront yani ba�a eleman ekleme olarak yap�caz. Mesela src'den dest'e bir edge eklemek i�in �nce dest etiketli bir node olu�turup sonra bu
node'un next'ine adjList[src]'yi at�ycaz. ��nk� adjList[src]'de src etiketli node'un kom�ular�n�n linkli listesi var ve adjList[src] bu linkli
listenin head g�revini g�r�yor. Ben dedi�im atamay� yap�nca yeni dest etiketli node'un head'in i�aret etti�i node'a i�aret etmesin sa�lad�m.
Sonras�nda adjList[src]'ye dest etiketli yeni yaratt���m node'un adresini atarsam head, yani adjList[src], art�k dest'in adresini tutuyor olur.

Bu bir undirected graph oldu�u i�in ayn� �eyi adjList[dest] i�in de yap�yoruz. directed olsayd� birisi yeterli olacakt�. 

Yani g�rd���n gibi n tane node yarat�p bunlar�n aras�nda ba�lant� kurmuyoruz. Bir node'a eklenen her bir node i�in o node'dan tekrar yarat�yoruz.
Mesela addEdge(0,3) ve addEdge(2,3) �a�r�lar� yap�lsa iki tane 3 etiketli node yaratm�� oluruz.
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
	addEdges(graph, 2, 3); // return olur, zaten eklenmi�ti.
	
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
	    printf("%d -> ", i); // hangi node'un kom�ular�.
	    NODE* temp = graph -> adjList[i];
	    while(temp != NULL) {
	        printf("%d, ", temp -> vertex);
	        temp = temp -> next;
	    }
	    printf("\n");
	}
}
