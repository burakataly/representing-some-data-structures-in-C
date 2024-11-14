#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define M 16
#define N 100 //the range of input keys

//linear probing is used with universal hashing

//for a set implementation, we dont need to store value and just store the key in the node
typedef struct node{
	int key; //will be -1 if node is empty, -2 if it is deleted and ready to reuse
	char* value;
}NODE;

typedef struct map{
	int m; //the number of chains (buckets) in the map
	int n; //the number of pairs currently in the map
	int p; //prime that is slightly bigger than the range of input keys N to use it in universal hash function
	int a; //number between [1, p-1] to use it in universal hash function
	int b; //number between [0, p-1] to use it in universal hash function
	NODE *hashMap;
}MAP;

int isPrime(int num);
int findNextPrime(int num);
int hashFunction(MAP* map, int key);
MAP* createHashMap(int m);
int hasKey(MAP* map, int key);
void set(MAP** map, int key, char* name);
char* get(MAP* map, int key);
void removePair(MAP* map, int key);
void freeMap(MAP* map);
MAP* resizeMap(MAP* map);
void printMap(MAP* map);

int main(){
	srand(time(0));
	int m = M, i;
	MAP* map = createHashMap(m);
	map->p = findNextPrime(N); //defining the hash function randomly from universal family before taking the inputs
	map->a = rand() % (map->p - 1) + 1;
	map->b = rand() % (map->p);
	
	set(&map, 12, "burak");
	set(&map, 14, "murat");
	set(&map, 25, "ali");
	
	for(i=0;i<17;i++){
		set(&map, i, "burak");
	}
	
	printMap(map);

	for(i=17;i<34;i++){
		printf("%d\n", map->m);
		set(&map, i, "burak");
	}
	removePair(map, 14);
	printMap(map);
	//set(&map, 600, "ali");
	//printMap(map);
	printf("%s\n", get(map, 14));
	printf("%d", hasKey(map, 34));
	return 0;
}

//hash function that applies universal hashing
int hashFunction(MAP* map, int key){
	return (((map->a * key) % map->p + map->b) % map->p) % map->m;
}

int findNextPrime(int num){
	int p = num + 1;
	
	while(!isPrime(p)){
		p++;
	};
	
	return p;
}

int isPrime(int num){
	int temp = sqrt(num), i;
	
	for(i=2;i<=temp;i++){
		if(num % i == 0) return 0;
	}
	
    return 1;
}

MAP* createHashMap(int m){
	MAP* map = (MAP*) calloc(1, sizeof(MAP));
	map->m = m;
	map->n = 0;
	map->hashMap = (NODE*) calloc(m, sizeof(NODE));
	int i;
	for(i=0;i<m;i++) map->hashMap[i].key = -1;
	return map;
}

int hasKey(MAP* map, int key){
	int k = hashFunction(map, key);
	int i = 0;
	
	while(i < map->m && map->hashMap[k].key != -1){ //if there is an empty slot while doing linear probing, then key cannot be in the map
		if(map->hashMap[k].key == key) return k; //returning the slot
		i++;
		k = (k + i) % map->m;
	};
	return -1; //has not
}

void set(MAP** map, int key, char* name){
	int k = hashFunction(*map, key);
	int i = 0;
	
	while(i < (*map)->m && (*map)->hashMap[k].key != -1 && (*map)->hashMap[k].key != -2){
		if((*map)->hashMap[k].key == key){ //if key is already in the chain, we change the value of the key - value pair.
			(*map)->hashMap[k].value = (char*) realloc((*map)->hashMap[k].value, (strlen(name) + 1) * sizeof(char));
			strcpy((*map)->hashMap[k].value, name);
			return;
		}
		i++;
		k = (k + i) % (*map)->m;
	};
	
	(*map)->hashMap[k].key = key;
	(*map)->hashMap[k].value = (char*) malloc((strlen(name) + 1) * sizeof(char));
	strcpy((*map)->hashMap[k].value, name);
	
	(*map)->n++;
	double load_factor = (*map)->n / (*map)->m;
	if(load_factor >= 0.7) *map = resizeMap(*map);
}

char* get(MAP* map, int key){
	int k = hasKey(map, key);
	return (k != -1) ? map->hashMap[k].value : "NOT FOUND"; 
}

void removePair(MAP* map, int key){
	int k = hasKey(map, key);
	
	if(k != -1){
		map->hashMap[k].key = -2;
		free(map->hashMap[k].value);
		map->n--;	
	}
}

void freeMap(MAP* map){
	int i;
	
	for(i=0;i<map->m;i++){
		free(map->hashMap[i].value);
	}
	
	free(map->hashMap);
	free(map);
}

/*
the complexity is O(n) for resizing since we get hash value of each key with new m and put it into its new bucket. But since we need to do it 
when n is doubled in size, the complexity can be calculated with amortized analysis like we do it in vector's complexity for adding new element.
complexity for adding new key for each adding operation is constant, O(1)...
*/
MAP* resizeMap(MAP* map){ //resizing the map if load factor becomes exceeds 1 since we would get long chains when it is bigger than 1
	int i;
	MAP* newMap = createHashMap(map->m * 2);
	newMap->p = map->p;
	newMap->a = rand() % (newMap->p - 1) + 1;
	newMap->b = rand() % (newMap->p);
	for(i=0;i<map->m;i++){
		if(map->hashMap[i].key >= 0){ //if slot is not empty or deleted
			set(&newMap, map->hashMap[i].key, map->hashMap[i].value);	
		}
	}
	freeMap(map);
	return newMap;
}

void printMap(MAP* map){
	int i;
	printf("\np: %d, a: %d, b:%d, n: %d, m: %d\n", map->p, map->a, map->b, map->n, map->m);
	for(i=0;i<map->m;i++){
		if(map->hashMap[i].key < 0){
			printf("%d -> Empty\n", i);
		}
		else printf("%d -> (%d, %s)\n", i, map->hashMap[i].key, map->hashMap[i].value);
	}
	printf("\n------------------------------------------------------------\n\n");
}
