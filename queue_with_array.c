#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int max_size;
	int size;
	int head;
	int tail;
	int* elements;
}QUEUE;

QUEUE* createQueue(int n){
	QUEUE* queue = (QUEUE*) malloc(sizeof(QUEUE));
	queue->max_size = n;
	queue->size = 0;
	queue->head = 0;
	queue->tail = -1;
	queue->elements = (int*) malloc(n * sizeof(int));
	return queue;	
}

int isFull(QUEUE* queue){
	return (queue->max_size == queue->size);	
}

int isEmpty(QUEUE* queue){
	return (queue->size == 0);
}

void enqueue(QUEUE* queue, int data){
	if(!isFull(queue)){
		queue->tail = (queue->tail + 1) % queue->max_size;
		queue->elements[queue->tail] = data;
		queue->size++;
	}
	else printf("queue is full\n");
}

int dequeue(QUEUE* queue){
	if(!isEmpty(queue)){
		int data = queue->elements[queue->head];
		queue->head = (queue->head + 1) % queue->max_size;
		queue->size--;
		return data;
	}
	else printf("queue is empty\n");
}

int main(){
	QUEUE* queue = createQueue(5);
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printf("Dequeued element: %d\n", dequeue(queue));
    printf("Dequeued element: %d\n", dequeue(queue));
    printf("Dequeued element: %d\n", dequeue(queue));
    enqueue(queue, 40);
    enqueue(queue, 50);
    enqueue(queue, 60);
	return 0;
}
