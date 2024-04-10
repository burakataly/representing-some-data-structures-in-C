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

void pushBack(node** tail, int i){
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

//node *m, kendisinden sonra node eklenecek node'un adresini tutuyor. Bu kuyruða eklemek için de çalýþýr.
void araya_ekle(node* m, int i){
	node* temp = (node*) malloc(sizeof(node));
	temp -> x = i;
	temp -> next = m -> next;
	m -> next = temp;
}

//baþtaki node'u silmek için
void popFront(node **head){
	if(*head == NULL) return;
	node* temp = *head;
	(*head) = (*head) -> next;
	free(temp);
}

void remove_node(node** head, int i){
	if(*head == NULL) return;
	
	node *temp = *head, *temp2;
	
	//eleman baþtaki node'daysa
	if((*head) -> x == i){
		(*head) = (*head) -> next;
		free(temp);
		return;
	}
	
	//lineer search yaparak elemaný arýyoz.
	while(temp -> next != NULL && i != temp -> next -> x){
		temp = temp -> next;
	}
	
	//eleman bulunamadýysa
	if(temp -> next == NULL){
		printf("\neleman bulunamadi.");
		return;
	}
	
	temp2 = temp -> next;
	temp -> next = temp -> next -> next;
	free(temp2);
}

void sirali_ekle(node** head, int i){
	node *temp = *head, *temp2;
	
	if(head == NULL){
		*head = (node*) malloc(sizeof(node));
		(*head) -> x = i;
		(*head) -> next = NULL;
		return;
	}
	
	//baþa ekliyosak, yani head deðiþiyosa
	if((*head) -> x >= i){
		temp = (node*) malloc(sizeof(node));
		temp -> next = *head;
		temp -> x = i;
		*head = temp;
		return;
	}
	
	//ikinci þart, adresini tuttuðumuz node'un öncesine node ekleyemememiz sebebiyle var.
	while(temp -> next != NULL && temp -> next -> x < i){
		temp = temp -> next;
	}
	
	//Aslýnda kuyruða eklenmeyle araya ekleme ayný iþlemmiþ, dikkat edersen... alttaki satýrlar hem kuyruða hem araya ekleme için çalýþýyo
	temp2 = (node*) malloc(sizeof(node));
	temp2 -> next = temp -> next;
	temp2 -> x = i;
	temp -> next = temp2;
}

int main(){
	int i;
	node *head, *tail, *temp;
	
	head = (node*) malloc(sizeof(node));
	head -> x = 0;
	head -> next = NULL;
	tail = head;
	
	for(i=1;i<=10;i++){
		pushBack(&tail, 2*i);
	}
	
	temp = head;
	for(i=0;i<3;i++){
		temp = temp -> next;
	}
	
	araya_ekle(temp, 7);
	
	sirali_ekle(&head, 50);
	sirali_ekle(&head, 9);
	sirali_ekle(&head, 18);
	sirali_ekle(&head, -10);
	sirali_ekle(&head, 37);
	sirali_ekle(&head, 11);
	
	//writeList(head);

	remove_node(&head, 50);
	
	writeList(head);
	return 0;
}
