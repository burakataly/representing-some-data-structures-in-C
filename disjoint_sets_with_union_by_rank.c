#include <stdio.h>
#include <stdlib.h>

/*
now we are going to represent each set as a tree in an abstract way. when we call makeSet for each node these nodes will be the root of their own sets.
so their parent will be themselves. and a union operation will be done in this way: the root of one of the sets is going to point to other one's root. it
can be done easily in a constant time by setting the root's parent to other root's index. find operation can be done by traversing parents until the parent
equals to node itself. so we can done it in a complexity of the height of the tree that this node belongs to.

So we got only one problem here: we should make the trees short. we can do it by adding the shorter tree to longer tree when doing union operation. 
if trees dont have same height, the heights wont change. we can look at the tree heights by storing rank field in nodes and looking at that value while
doing union. 

now we are going to prove that each set, or tree, with n nodes have at most logn height.
we should first prove that a set with height k has at least 2^k nodes.
proof by induction on k: 
base case: for k = 0, a tree has one node.
induction step: assuming the hypothesis is true for k, we should prove that is true for k+1. a tree with height k can only have k+1 height if it is having a
union operation with a tree with height k. so these two trees have at least 2^k nodes each from hypothesis and after the union we will have 2^k + 2^k = 2^(k+1)
nodes for a tree with height k+1.

now we can prove that a tree with n nodes has at most log2(n) height. we can use the lemma we proved just now. 
proof by contradiction: assume that we have a set with n nodes that has a height bigger than log2(n), then we would have more then 2^(log2(n)) nodes according
to the above proof and that means we would have more then n nodes and that creates a contradiction.

So we have logn complexity for find and union operation in worst case...   
*/

typedef struct {
	int parent;
	int rank;
}node;

// O(1)
void makeSet(node* nodes, int n, int i){
	if(i < 1 || i > n) return;
	nodes[i-1].parent = i;
	nodes[i-1].rank = 0;
}

// O(height of the tree that i belongs to)
int find(node* nodes, int n, int i){
	if(i < 1 || i > n) return;
	while(i != nodes[i-1].parent) i = nodes[i-1].parent;
	return i;
}

// O(height of the tree that i belongs to + height of the tree that j belongs to)
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
	for(i=0;i<n;i++) printf("(parent: %d - rank: %d) ", nodes[i].parent, nodes[i].rank);
	printf("\n");
}

int main(){
	int n = 12, i;
	node* nodes = (node*) malloc(n * sizeof(node));
	for(i=1;i<=n;i++) makeSet(nodes, n, i);
	printNodes(nodes, n);
	/**/
	setUnion(nodes, n, 2, 10);
	setUnion(nodes, n, 7, 5);
	setUnion(nodes, n, 6, 1);
	setUnion(nodes, n, 3, 4);
	setUnion(nodes, n, 5, 11);
	setUnion(nodes, n, 7, 8);
	setUnion(nodes, n, 7, 3);
	setUnion(nodes, n, 12, 2);
	setUnion(nodes, n, 9, 6);
	
	//for(i=1;i<n;i++) setUnion(nodes, n, i, i+1);
	printNodes(nodes, n);
	return 0;
}
