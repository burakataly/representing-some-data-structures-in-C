#include <stdio.h>
#include <stdlib.h>

/*
at the begining of the program, we are creating n sets by using makeSet function for n items. these are going to be ids for each set. and after a union
operation if these two items are not in the same set then we are going to take the minimum id out of two and make a linear search to find item with one of 
these two ids and set their ids to min.
*/
 
// O(1)
void makeSet(int* sets, int n, int i){
	if(i < 1 || i > n) return;
	sets[i-1] = i;
}

// O(1)
int find(int* sets, int n, int i){
	if(i < 1 || i > n) return;
	return sets[i-1];
}

// O(n)
void setUnion(int* sets, int n, int i, int j){
	if(i < 1 || i > n || j < 1 || j > n) return;
	int id1 = find(sets, n, i);
	int id2 = find(sets, n, j);
	if(id1 == id2) return;
	int k, min;
	min = (id1 > id2) ? id2 : id1;
	for(k=0;k<n;k++){
		if(sets[k] == id2 || sets[k] == id1) sets[k] = min;
	}
}

void printSets(int* sets, int n){
	int i;
	printf("\n");
	for(i=0;i<n;i++) printf("%d ", sets[i]);
	printf("\n");
}

int main(){
	int n = 12, i;
	int* sets = (int*) malloc(n * sizeof(int));
	
	for(i=1;i<=n;i++) makeSet(sets, n, i);
	
	printSets(sets, n);
	/*
	printf("%d\n", find(sets, n, 1) == find(sets, n, 2));
	
	setUnion(sets, n, 1, 2);
	
	printf("%d\n", find(sets, n, 1) == find(sets, n, 2));
	*/
	
	setUnion(sets, n, 7, 5);
	setUnion(sets, n, 6, 1);
	setUnion(sets, n, 3, 4);
	setUnion(sets, n, 5, 11);
	setUnion(sets, n, 7, 8);
	setUnion(sets, n, 7, 3);
	setUnion(sets, n, 12, 2);
	setUnion(sets, n, 9, 6);
	printSets(sets, n);
	printf("%d\n", find(sets, n, 6));
	printf("%d\n", find(sets, n, 3));
	printf("%d\n", find(sets, n, 11));
	printf("%d\n", find(sets, n, 9));
	printSets(sets, n);
	
	return 0;
}
