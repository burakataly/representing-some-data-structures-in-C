#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int x;
	struct n* prev;
	struct n* next;
}node;

//prevler doðru atanmýþ mý diye bakmak için önce son node'a gidip ordan prev yaparak yazdýrdým yani büyükten küçüðe sýralý yazdýrýr
void writeList(node* head){
	while(head -> next != NULL){
		head = head -> next;
	}
	
	while(head != NULL){
		printf("%d ", head -> x);
		head = head -> prev;
	}
	printf("\n");
}

void sirali_ekle(node** head, int i){
	//linked list boþsa
	if(*head == NULL){
		*head = (node*) malloc(sizeof(node));
		(*head) -> x = i;
		(*head) -> prev = NULL;
		(*head) -> next = NULL;
		return;
	}
	//yeni eleman baþa konulcaksa, yani head deðiþiyosa
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
	//ikinci þart temp -> x < i olarak deðiþebilir çünkü bir geri gidebilme þansýmýz var prev'i tuttuðumuzdan dolayý.
	//Yani adresini tuttuðumuz node'un öncesine node ekleyebilirz.
	while(temp -> next != NULL && temp -> next -> x < i){
		temp = temp -> next;
	}
	
	//sona ekliyosak (normal linked listte sona ve araya eklemek ayný ama bunda sýkýntý çýkýyo)
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

void remove_node(node **head, int i){
	if(*head == NULL) return;
	
	node *temp = *head, *temp2;
	if((*head) -> x == i){
		(*head) = (*head) -> next;
		(*head) -> prev = NULL;
		free(temp);
		return;
	}
	
	//eleman mevcutsa temp, döngüden çýktýðýnda sileceðimiz node'un adresini tutuyo olacak. 
	while(temp != NULL && i != temp -> x){
		temp = temp -> next;
	}
	
	if(temp == NULL){
		printf("\neleman bulunamadi.");
		return;
	}
	
	temp -> prev -> next = temp -> next; //temp'den önceki node'un next'ine tempin next'ini atýycaz
	if(temp -> next != NULL) temp -> next -> prev = temp -> prev; //tempden sonraki node'un prev'ine temp'in prev'ini atýycaz, ama temp son node ise bunu yapmamalýyýz.
	free(temp);
}

int main(){
	node *head = NULL;
	
	sirali_ekle(&head, 50);
	sirali_ekle(&head, -10);
	sirali_ekle(&head, 17);
	sirali_ekle(&head, 63);
	sirali_ekle(&head, 23);
	
	writeList(head);
	
	remove_node(&head, 63);
	writeList(head);
	return 0;
}
