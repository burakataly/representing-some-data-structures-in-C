#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int parent;
	int rank;
}node;


void makeSet(node* nodes, int n, int i){
	if(i < 1 || i > n) return;
	nodes[i-1].parent = i;
	nodes[i-1].rank = 0;
}

int find(node* nodes, int n, int i){
	if(i < 1 || i > n) return;
	if(i != nodes[i-1].parent) nodes[i-1].parent = find(nodes, n, nodes[i-1].parent);
	return nodes[i-1].parent;
}

void setUnion(node* nodes, int n, int i, int j){
	if(i < 1 || i > n || j < 1 || j > n) return;
	int id1 = find(nodes, n, i);
	int id2 = find(nodes, n, j);
	if(id1 == id2) return;
	if(nodes[id1 - 1].rank > nodes[id2 - 1].rank){
		nodes[id2 - 1].parent = id1;
	}
	else{
		nodes[id1 - 1].parent = id2;
		if(nodes[id1 - 1].rank == nodes[id2 - 1].rank){
			nodes[id2 - 1].rank++;
		}
	}
}

void printNodes(node* nodes, int n){
	int i;
	printf("\n");
	for(i=0;i<n;i++) printf("(parent: %d - rank: %d) \n", nodes[i].parent, nodes[i].rank);
	printf("\n");
}

int main(){
	int n = 60, i;
	node* nodes = (node*) malloc(n * sizeof(node));
	for(i=1;i<=n;i++) makeSet(nodes, n, i);
	//printNodes(nodes, n);
	/*
	setUnion(nodes, n, 2, 10);
	setUnion(nodes, n, 7, 5);
	setUnion(nodes, n, 6, 1);
	setUnion(nodes, n, 3, 4);
	setUnion(nodes, n, 5, 11);
	setUnion(nodes, n, 7, 8);
	setUnion(nodes, n, 7, 3);
	setUnion(nodes, n, 12, 2);
	setUnion(nodes, n, 9, 6);*/
	for(i=1;i<=30;i++) setUnion(nodes, n, i, 2 * i);
	for(i=1;i<=20;i++) setUnion(nodes, n, i, 3 * i);
	for(i=1;i<=12;i++) setUnion(nodes, n, i, 5 * i);
	for(i=1;i<=n;i++) find(nodes, n, i);
	//for(i=1;i<n;i++) setUnion(nodes, n, i, i+1);
	printNodes(nodes, n);
	return 0;
}
