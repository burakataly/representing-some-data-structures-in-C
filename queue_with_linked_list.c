#include <stdio.h>
#include <stdlib.h>

//queue için ilk giren son çýkar mantýðý vardýr.

typedef struct n{
	int x;
	struct n* next;
}node;

typedef struct q{
    node* head;
    node* tail;
}QUEUE;

void push(QUEUE* queue, int i){
	node *temp = (node*) malloc(sizeof(node));
	temp -> x = i;
	temp -> next = NULL;
	if(queue -> tail == NULL){
		queue -> tail = temp;
		queue -> head = temp;
	}
	else{
		queue -> tail -> next = temp;
		queue -> tail = temp;
	}
}

int pop(QUEUE* queue){
	if(queue -> head != NULL){
        int result = queue -> head -> x;
        node *temp = queue -> head;
        queue -> head = queue -> head -> next;
        if(queue -> head == NULL) queue -> tail = NULL;
        free(temp);
        return result;
    }
}

int main(){
	QUEUE* queue = (QUEUE*) calloc(1, sizeof(QUEUE));
	
	push(queue, 1);
	push(queue, 11);
	push(queue, 2);
	push(queue, 41);
	push(queue, 7);
	push(queue, 8);
	printf("%d\n", pop(queue));
	printf("%d\n", pop(queue));

	return 0;
}
