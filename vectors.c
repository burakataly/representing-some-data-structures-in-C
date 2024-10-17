#include <stdio.h>
#include <stdlib.h>

/*
this is an implementaion from scratch of vectors in C++. in amortized analysis the complexity of each append operation is O(1). adding a new element is
O(1) when array is not full. it is O(n) only when array is full and we do reallocating.

Amortized analysis: so since we make the capacity 2 when create the vector and multiply by 2 when reallocating space, we only reallocate when size becomes
power of 2. when size is not power of 2, the complexity of adding an element is O(1). the complexity of adding an element when size is power of 2 is 
O(current size). so for n append operation we will have total of n * O(1) = O(n) complexity for adding and also O(i) for all numbers i that are power of
2 up to n. first number is 2^0 and last is 2^log(n). if you do the sum of geometric series, you get O(n) from second part as well. so you get O(n) + O(n)
complexity in total. for n operation we get O(n) complexity. so for each operation we get O(1) complexity...
*/

typedef struct{
	int *arr;
	int capacity;
	int size;
}VECTOR;

VECTOR* createVector();
void append(VECTOR* vector, int i);
void pop(Vector* vector);

int main(){
	VECTOR* vector = createVector();
	int i, n = 100;
	
	for(i=0;i<n;i++){
		append(vector, i);	
	}
	
	for(i=0;i<vector->size;i++){
		printf("%d ", i);	
	}
	
	return 0;
}

VECTOR* createVector(){
	VECTOR* vector = (VECTOR*) malloc(sizeof(VECTOR));
	if(vector == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
	vector->capacity = 2;
	vector->size = 0;
	vector->arr = (int*) malloc(2 * sizeof(int));
	if(vector->arr == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
	return vector;
}

void append(VECTOR* vector, int i){
	if(vector->size == vector->capacity){
		vector->capacity *= 2;
		int* temp = (int*) realloc(vector->arr, vector->capacity * sizeof(int));
		if(temp != NULL){
			vector->arr = temp;
		}
		else{
			printf("Memory allocation failed!\n");
			exit(1);
		}
	}
	
	vector->arr[vector->size++] = i;
}

void pop(Vector* vector){
	vector->size--;
	if(4 * vector->size == vector->capacity){ //make the array smaller since 3/4 of the space is wasted
		vector->capacity /= 4;
		int* temp = (int*) realloc(vector->arr, vector->capacity * sizeof(int));
		if(temp != NULL){
			vector->arr = temp;
		}
		else{
			printf("Memory allocation failed!\n");
			exit(1);
		}
	}
}

