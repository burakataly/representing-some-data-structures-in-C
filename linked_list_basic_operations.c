#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int x;
	struct n* next;
} node;

void writeList(node* head){
	while(head != NULL){
		printf("\n%d", head -> x);
		head = head -> next;
	}
}

//sondaki node'un adresini biliyorsak sondaki node'un adresini fonksiyona veririz ve bir node ekleyip bu yeni node'un adresini returnleriz.
//yani son node'un adresini hiç kaybetmeyiz, bu sayede sona eleman ekleme O(1) karmaþýklýkta olur.

node* pushBack1(node* tail, int i){
	if(tail == NULL){
		tail = (node*) malloc(sizeof(node));
		tail -> x = i;
		tail -> next = NULL;
		return tail;
	}
	tail -> next = (node*) malloc(sizeof(node));
	tail = tail -> next;
	tail -> x = i;
	tail -> next = NULL;
	return tail;
}

//tail'in tuttuðu adresi fonksiyonun içinde deðiþtirmek için tail'in adresini fonksiyona gönderip iþlem yaptýk. Böylece return maliyetinden
//kurtulduk.

void pushBack1_2(node** tail, int i){
	if(*tail == NULL){
		*tail = (node*) malloc(sizeof(node));
		(*tail) -> x = i;
		(*tail) -> next = NULL;
		return;
	}
	(*tail) -> next = (node*) malloc(sizeof(node));
	(*tail) = (*tail) -> next;
	(*tail) -> x = i;
	(*tail) -> next = NULL;
}

//sondaki node'un adresini bilmiyorsak fonksiyona head'in adresini veririz ve son node'a kadar ilerleyip sonrasýnda buna eleman ekleriz. Yani
//sona eleman ekleme O(n) karmaþýklýkta olur.

void pushBack2(node* head, int i){
	while(head -> next != NULL){
		head = head -> next;
	}
	
	head -> next = (node*) malloc(sizeof(node));
	head = head -> next;
	head -> x = i;
	head -> next = NULL;
}

//baþa eleman eklemek için
node* pushFront1(node* head, int i){
	node* temp;
	temp = (node*) malloc(sizeof(node));
	temp -> next = head;
	temp -> x = i;
	head = temp;
	return head;
}

//baþa eleman eklerken head'in tuttuðu deðeri doðrudan deðiþtirmek için 
void pushFront2(node** head, int i){
	node* temp;
	temp = (node*) malloc(sizeof(node));
	if(*head == NULL){
		*head = temp;
		(*head) -> x = i;
		(*head) -> next = NULL;
		return;
	}
	temp -> next = *head;
	temp -> x = i;
	*head = temp;
}

//baþtaki node'u silmek için
void popFront(node **head){
	if(*head == NULL) return;
	node* temp = *head;
	(*head) = (*head) -> next;
	free(temp);
}

int main(){
	int i;
	node *head, *tail;
	
	head = (node*) malloc(sizeof(node));
	head -> x = 0;
	head -> next = NULL;
	tail = head;
	
//	for(i=1;i<=5;i++){
//		tail = pushBack1(tail, i);
//	}

	for(i=1;i<=5;i++){
		pushBack1_2(&tail, i+10);
	}
	
	printf("\nafter pushBack1...");
	writeList(head);

	for(i=1;i<=5;i++){
		pushBack2(head, i+5);
	}
	
	printf("\nafter pushBack2...");
	writeList(head);
	
//	for(i=1;i<=5;i++){
//		head = pushFront(head, (-1)*i);
//	}
	
	for(i=1;i<=5;i++){
		pushFront2(&head, (-1)*i);
	}
	
	printf("\nafter pushFront...");
	writeList(head);
	
	popFront(&head);
	printf("\n\n");
	writeList(head);

	return 0;
}
