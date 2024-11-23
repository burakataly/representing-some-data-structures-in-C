#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int x;
	struct n* next;
}stack;

//linked list olan� i�in fonklar
void push(stack **head, int i){
	stack *temp = (stack*) malloc(sizeof(stack));
	temp -> x = i;
	temp -> next = *head;
	*head = temp;
}

void top(stack *head){
	if(head == NULL) printf("stack is empty");
	else printf("%d\n", head -> x);
}

void pop(stack **head){
	if(*head == NULL) printf("stack is already empty...");
	else{
		stack *temp = *head;
		*head = (*head) -> next;
		printf("the element about to be removed is: %d\n", temp -> x);
		free(temp);
	}
}

//array olan� i�in olan fonklar
void push2(int *stack, int *top, int i, int n){
	if(*top == n){
		printf("stack is full");
	}
	else{
		(*top)++;
		stack[*top] = i;
	}
}

void top2(int *stack, int top){
	if(top == -1) printf("stack is empty");
	else printf("%d\n", stack[top]);
}

void pop2(int *stack, int* top){
	if(*top == -1) printf("stack is already empty...");
	else{
		printf("the element about to be removed is: %d\n", stack[*top]);
		(*top)--;
	}
}

int main(){
	stack* head = NULL, *temp;
	int stack2[100], n=100,top=-1, i;
	push(&head, 1);
	push(&head, 11);
	push(&head, 2);
	push(&head, 41);
	push(&head, 7);
	push(&head, 8);
	pop(&head);
	
	temp = head;
	while(temp != NULL){
		printf("%d ", temp -> x);
		temp = temp -> next;
	}
	
	push2(stack2, &top, 1, n);
	push2(stack2, &top, 11, n);
	push2(stack2, &top, 2, n);
	push2(stack2, &top, 41, n);
	push2(stack2, &top, 7, n);
	push2(stack2, &top, 8, n);
	pop2(stack2, &top);
	
	for(i=top;i>=0;i--) printf("%d ", stack2[i]);

	return 0;
}
