#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define M 11

//for a set implementation, we dont need to store value and just store the key in the node
typedef struct node{
	int key;
	char* value;
	struct node* next;
}NODE;

typedef struct map{
	int m;
	int n;
	NODE **chainingList;
}MAP;

int hashFunction_div(int key, int m);//using division method
int hashFunction_mul(int key, int m);//using multiplication method
MAP* createHashMap(int m);
NODE* createNewNode(int key, char* name);
int hasKey(MAP* map, int key);
void set(MAP** map, int key, char* name);
char* get(MAP* map, int key);
void removePair(MAP* map, int key);
void freeMap(MAP* map);
MAP* resizeMap(MAP* map);
void printMap(MAP* map);

int main(){
	int m = M;
	MAP* map = createHashMap(m);
	set(&map, 12, "burak");
	set(&map, 14, "murat");
	set(&map, 25, "ali");
	removePair(map, 14);
	printMap(map);
	printf("%s\n", get(map, 14));
	printf("%d", hasKey(map, 34));
	return 0;
}

int hashFunction_div(int key, int m){
	return key % m;
}

//using multiplication method
int hashFunction_mul(int key, int m){
	double A = (sqrt(5) - 1.0) / 2.0;
	double temp = A * key;
	return (temp - floor(temp)) * m;
}

MAP* createHashMap(int m){
	MAP* map = (MAP*) calloc(1, sizeof(MAP));
	map->m = m;
	map->n = 0;
	map->chainingList = (NODE**) calloc(m, sizeof(NODE*));
	return map;
}

NODE* createNewNode(int key, char* name){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node->key = key;
	node->value = (char*) malloc((strlen(name) + 1) * sizeof(char));
	strcpy(node->value, name);
	return node;
}

int hasKey(MAP* map, int key){
	int chain = hashFunction_div(key, map->m);
	NODE* temp = map->chainingList[chain]; 
	while(temp != NULL){
		if(temp->key == key) return 1;
		temp = temp->next;
	};
	return 0;
}

void set(MAP** map, int key, char* name){
	int chain = hashFunction_div(key, (*map)->m);
	NODE* temp = (*map)->chainingList[chain];
	
	while(temp != NULL){
		if(temp->key == key){ //if key is already in the chain, we change the value of the key - value pair.
			temp->value = (char*) realloc(temp->value, (strlen(name) + 1) * sizeof(char));
			strcpy(temp->value, name);
			return;
		}
		temp = temp->next;
	};
	
	NODE* node = createNewNode(key, name);
	node->next = (*map)->chainingList[chain];
	(*map)->chainingList[chain] = node;
	
	(*map)->n++;
	double load_factor = (*map)->n / (*map)->m;
	if(load_factor >= 1) *map = resizeMap(*map);
}

char* get(MAP* map, int key){
	int chain = hashFunction_div(key, map->m);
	NODE* temp = map->chainingList[chain];
	while(temp != NULL && temp->key != key){
		temp = temp->next;
	};
	return (temp != NULL) ? temp->value : "NOT FOUND"; 
}

void removePair(MAP* map, int key){
	int chain = hashFunction_div(key, map->m);
	NODE* temp = map->chainingList[chain];
	
	if(temp == NULL) return;
	if(temp->key == key){
		map->chainingList[chain] = temp->next;
		free(temp);
		return;
	}
	
	while(temp->next != NULL && temp->next->key != key){
		temp = temp->next;
	}
	
	if(temp->next == NULL) return;
	
	NODE* temp2 = temp->next;
	temp->next = temp->next->next;
	free(temp2);
}

void freeMap(MAP* map){
	int i;
	
	for(i=0;i<map->m;i++){
		NODE* temp = map->chainingList[i];
        while(temp != NULL){
            NODE* deleting = temp;
            temp = temp->next;
            free(deleting);
        }
	}
	
	free(map->chainingList);
	free(map);
}

MAP* resizeMap(MAP* map){
	int i;
	MAP* newMap = createHashMap(map->m * 2);
	for(i=0;i<map->m;i++){
		NODE* temp = map->chainingList[i];
		while(temp != NULL){
			set(&newMap, temp->key, temp->value);
			temp = temp->next;
		}
	}
	newMap->n = map->n;
	free(map);
	return newMap;
}

void printMap(MAP* map){
	NODE* temp;
	int i;
	for(i=0;i<map->m;i++){
		temp = map->chainingList[i];
		printf("%d", i);
		while(temp != NULL){
			printf(" -> (%d, %s)", temp->key, temp->value);
			temp = temp->next;
		}
		printf("\n");
	}
}
