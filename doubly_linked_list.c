#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int x;
	struct n* prev;
	struct n* next;
}node;

void printList(node* head){
	while(head -> next != NULL){
		head = head -> next;
	}
	
	while(head != NULL){
		printf("%d ", head -> x);
		head = head -> prev;
	}
	printf("\n");
}

void addSorted(node** head, int i){
	if(*head == NULL){
		*head = (node*) malloc(sizeof(node));
		(*head) -> x = i;
		(*head) -> prev = NULL;
		(*head) -> next = NULL;
		return;
	}
	if((*head) -> x >= i){
		node* temp = (node*) malloc(sizeof(node));
		temp -> x = i;
		temp -> prev = NULL;
		temp -> next = *head;
		(*head) -> prev = temp;
		*head = temp;
		return;
	}
	
	node *temp = *head, *temp2;

	while(temp -> next != NULL && temp -> next -> x < i){
		temp = temp -> next;
	}
	
	if(temp -> next == NULL){
		temp2 = (node*) malloc(sizeof(node));
		temp2 -> x = i;
		temp2 -> next = NULL;
		temp2 -> prev = temp;
		temp -> next = temp2;
		return;
	}
	
	temp2 = (node*) malloc(sizeof(node));
	temp2 -> x = i;
	temp2 -> prev = temp;
	temp2 -> next = temp -> next;
	temp -> next -> prev = temp2;
	temp -> next = temp2;
}

void removeNode(node **head, int i){
	if(*head == NULL) return;
	
	node *temp = *head, *temp2;
	if((*head) -> x == i){
		(*head) = (*head) -> next;
		(*head) -> prev = NULL;
		free(temp);
		return;
	}
	
	while(temp != NULL && i != temp -> x){
		temp = temp -> next;
	}
	
	if(temp == NULL){
		printf("\neleman bulunamadi.");
		return;
	}
	
	temp -> prev -> next = temp -> next;
	if(temp -> next != NULL) temp -> next -> prev = temp -> prev;
	free(temp);
}

int main(){
	node *head = NULL;
	
	addSorted(&head, 50);
	addSorted(&head, -10);
	addSorted(&head, 17);
	addSorted(&head, 63);
	addSorted(&head, 23);
	
	printList(head);
	
	removeNode(&head, 63);
	printList(head);
	return 0;
}
