#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define M 11
#define N 1000 //the range of input keys

/*
universal hashing is having a prime number p which is slightly bigger than the range of input keys and selecting a and b values randomly in range (0, p-1).
and do this at the begining of the program before getting input keys and also do it when resizing the hash table. and we apply hash function (a * x + b) % p
to each key. this is called universal hash function when we select a and b randomly as I said.
 
if we know the input range for example in a case where keys are phone numbers then no problem. But if we dont know the range of input keys then we can select
a big prime number initially and make it smaller if input range becomes too smaller than it. we need to do this since if prime number is much bigger than N than
there would not be good distribution and we get long chains...

we do resizing to make the load factor (number of keys in the table / number of buckets) slightly less than 1 to make the hash table operations efficient.
and as I said above the resizing function, the complexity of adding a new key to table is O(1) since we do resizing only when n is doubled...
*/ 

//for a set implementation, we dont need to store value and just store the key in the node
typedef struct node{
	int key;
	char* value;
	struct node* next;
}NODE;

typedef struct map{
	int m; //the number of chains (buckets) in the map
	int n; //the number of pairs currently in the map
	int p; //prime that is slightly bigger than the range of input keys N to use it in universal hash function
	int a; //number between [1, p-1] to use it in universal hash function
	int b; //number between [0, p-1] to use it in universal hash function
	NODE **chainingList; //list of chains
}MAP;

int isPrime(int num);
int findNextPrime(int num);
int hashFunction(MAP* map, int key);
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

	for(i=17;i<500;i++){
		set(&map, i, "burak");
	}
	removePair(map, 14);
	printMap(map);
	set(&map, 600, "ali");
	printMap(map);
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
	int chain = hashFunction(map, key);
	NODE* temp = map->chainingList[chain]; 
	while(temp != NULL){
		if(temp->key == key) return 1;
		temp = temp->next;
	};
	return 0;
}

void set(MAP** map, int key, char* name){
	int chain = hashFunction(*map, key);
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
	int chain = hashFunction(map, key);
	NODE* temp = map->chainingList[chain];
	while(temp != NULL && temp->key != key){
		temp = temp->next;
	};
	return (temp != NULL) ? temp->value : "NOT FOUND"; 
}

void removePair(MAP* map, int key){
	int chain = hashFunction(map, key);
	NODE* temp = map->chainingList[chain];
	
	if(temp == NULL) return;
	if(temp->key == key){
		map->chainingList[chain] = temp->next;
		free(temp);
		map->n--;
		return;
	}
	
	while(temp->next != NULL && temp->next->key != key){
		temp = temp->next;
	}
	
	if(temp->next == NULL) return;
	
	NODE* temp2 = temp->next;
	temp->next = temp->next->next;
	free(temp2);
	map->n--;
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

/*
the complexity is O(n) for resizing since we get hash value of each key with new m and put it into its new bucket. But since we need to do it 
when n is doubled in size, the complexity can be calculated with amortized analysis like we do it in vector's complexity for adding new element.
complexity for adding new key for each adding operation is constant, O(1)...
*/
MAP* resizeMap(MAP* map){ //resizing the map if load factor becomes exceeds 1 since we would get long chains when it is bigger than 1
	printf("resizing... m: %d\n", map->m);
	int i, newSize = findNextPrime(map->m * 2); //doubled the size and also selected the smallest prime bigger than that number
	MAP* newMap = createHashMap(newSize);
	newMap->p = map->p;
	newMap->a = rand() % (newMap->p - 1) + 1;
	newMap->b = rand() % (newMap->p);
	for(i=0;i<map->m;i++){
		NODE* temp = map->chainingList[i];
		while(temp != NULL){
			set(&newMap, temp->key, temp->value);
			temp = temp->next;
		}
	}
	
	freeMap(map);
	return newMap;
}

void printMap(MAP* map){
	NODE* temp;
	int i;
	printf("\np: %d, a: %d, b:%d, n: %d, m: %d\n", map->p, map->a, map->b, map->n, map->m);
	for(i=0;i<map->m;i++){
		temp = map->chainingList[i];
		printf("%d", i);
		while(temp != NULL){
			printf(" -> (%d, %s)", temp->key, temp->value);
			temp = temp->next;
		}
		printf("\n");
	}
	printf("\n------------------------------------------------------------\n\n");
}
