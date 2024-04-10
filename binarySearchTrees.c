#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
}NODE;

typedef struct n{
	NODE* x;
	struct n* next;
}qnode;

typedef struct q{
    qnode* head;
    qnode* tail;
    int size;
}QUEUE;

NODE* createNode(int key);
NODE* insertNode(int key, NODE* node);
void insertNode2(int key, NODE** root);
void deleteNode(NODE** root, int key);
NODE* deleteNode2(NODE* root, int key);
void preorder(NODE* root);
void BFS(NODE* root);
NODE* find(NODE* root, int key);
NODE* nextLargest(NODE* root, int key);
NODE* nextLargest2(NODE* node);
NODE* descendant(NODE* node);
NODE* ancestor(NODE* node);
NODE* helper(int* nums, int l, int r);
NODE* sortedArrayToBST(int* nums, int numsSize);
void rangeSearch(int x, int y, NODE* root);
void push(QUEUE* queue, NODE* i);
NODE* pop(QUEUE* queue);

int main(){
	NODE* root = NULL, *node;
	root = insertNode(5, root);
	insertNode(3, root);
	insertNode(2, root);
	insertNode(1, root);
	
	insertNode(4, root);
/*	insertNode(7, root);
	insertNode(6, root);
	insertNode(9, root);
	insertNode(10, root);
	preorder(root);*/
	printf("\n");
//	int arr[9] = {1,2,3,4,5,6,7,8,9};
//	root = sortedArrayToBST(arr, 9);
//	preorder(root);
	deleteNode(&root, 2);
	BFS(root);
	/*insertNode2(8, &root);
	int i;
	for(i=1;i<=10;i++){
		node = find(root, i);
		(node == NULL || node -> parent == NULL) ? printf("%d: NULL\n", i) : printf("%d: %d\n", i, node -> parent -> key);
	}
	node = find(root, 1);
	(node != NULL) ? printf("%d\n", node -> key) : printf("NOT EXIST\n");
	node = nextLargest(root, 5);
	(node != NULL) ? printf("%d\n", node -> key) : printf("NOT EXIST\n");
	rangeSearch(5, 9, root);
	
	node = find(root, 8);
	deleteNode(node);
	preorder(root);
	printf("\n");

	node = find(root, 2);
	deleteNode(node);
	preorder(root);
	printf("\n");
	
	root = deleteNode2(root, 5);
	BFS(root);
	printf("\n");*/
	return 0;
}

NODE* createNode(int key){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node -> key = key;
	return node;
}

//binary search yardýmýyla ekleme yapýlýyor. Ancak self balanced bir bst deðil tabii ki.
NODE* insertNode(int key, NODE* node){
	if(node == NULL) return createNode(key);
	if(node -> key >= key){
		node -> left = insertNode(key, node -> left);
		node -> left -> parent = node; //parent'ýný ekleme ihityacý varsa diye
	} 
	if(node -> key < key){
		node -> right = insertNode(key, node -> right);
		node -> right -> parent = node;
	}
	return node;
}

void insertNode2(int key, NODE** root){
	NODE* node = find(*root, key);
	if(node == NULL) *root = createNode(key);
	if(node -> key >= key){
		node -> left = createNode(key);
		node -> left -> parent = node; //parent'ýný ekleme ihityacý varsa diye
	}
	if(node -> key < key){
		node -> right = createNode(key);
		node -> right -> parent = node;
	} 
}

void deleteNode(NODE** root, int key){
	NODE* node = find(*root, key);
	if(node -> right == NULL){
		if(node -> parent != NULL){
			if(node -> key > node -> parent -> key) node -> parent -> right = node -> left;
			else node -> parent -> left = node -> left;
		}
		else *root = node -> left;
		
		if(node -> left != NULL) node -> left -> parent = node -> parent;
		free(node);
	}
	else{
		NODE* next = nextLargest2(node);
		if(next -> key > next -> parent -> key) next -> parent -> right = next -> right;
		else next -> parent -> left = next -> right;
		if(next -> right != NULL) next -> right -> parent = next -> parent;
		node -> key = next -> key;
		free(next);
	}
}

NODE* deleteNode2(NODE* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key) {
        root->left = deleteNode2(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode2(root->right, key);
    } else {
		NODE* temp;
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }
        temp = descendant(root->right);
        root->key = temp->key;
        root->right = deleteNode2(root->right, temp->key);
    }
    return root;
}

void preorder(NODE* root){
    if(root == NULL) return;
    printf("%d ", root -> key);
    preorder(root -> left);
    preorder(root -> right);
}

void BFS(NODE* root){
	QUEUE* queue = (QUEUE*) calloc(1, sizeof(QUEUE));
	int i, currentSize;
	NODE* temp;
	push(queue, root);
	while(queue -> head != NULL){
		currentSize = queue -> size;
		for(i=0;i<currentSize;i++){
			temp = pop(queue);
			printf("%d ", temp -> key);
			if(temp -> left != NULL) push(queue, temp -> left);
			if(temp -> right != NULL) push(queue, temp -> right);
		}
		printf("\n");
	}
	printf("\n");
}

NODE* find(NODE* root, int key){
	if(root == NULL) return NULL;
	if(root -> key == key) return root;
	if(root -> key >= key) return (root -> left != NULL) ? find(root -> left, key) : root;
	if(root -> key < key) return (root -> right != NULL) ? find(root -> right, key) : root;
}

NODE* nextLargest(NODE* root, int key){
	NODE* found = find(root, key);
	if(found == NULL) return NULL;
	if(found -> right != NULL) return descendant(found -> right);
	else return ancestor(found);
}

NODE* descendant(NODE* node){
	return (node -> left != NULL) ? descendant(node -> left) : node;
}

NODE* ancestor(NODE* node){
	if(node -> parent == NULL) return NULL;
	if(node -> key < node -> parent -> key) return node -> parent;
	return ancestor(node -> parent);
}

NODE* nextLargest2(NODE* node){
	if(node == NULL) return NULL;
	if(node -> right != NULL) return descendant(node -> right);
	else return ancestor(node);
}

NODE* helper(int* nums, int l, int r){
    if(l > r) return 0;
    int mid = l + (r-l) / 2;
    NODE* root = (NODE*) malloc(sizeof(NODE));
    root -> key = nums[mid];
    root -> left = helper(nums, l, mid-1);
    root -> right = helper(nums, mid+1, r);
    return root;
}

NODE* sortedArrayToBST(int* nums, int numsSize) {    
    return helper(nums, 0, numsSize - 1);
}

void rangeSearch(int x, int y, NODE* root){
	if(root == NULL) return;
	NODE* node = find(root, x);
	while(node != NULL && node -> key <= y){
		if(node -> key >= x) printf("%d ", node -> key);
		node = nextLargest2(node);
	}
	printf("\n");
}

void push(QUEUE* queue, NODE* i){
	qnode *temp = (qnode*) malloc(sizeof(qnode));
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
	queue -> size++;
}

NODE* pop(QUEUE* queue){
	if(queue -> head != NULL){
        NODE* result = queue -> head -> x;
        qnode *temp = queue -> head;
        queue -> head = queue -> head -> next;
        if(queue -> head == NULL) queue -> tail = NULL;
        free(temp);
        queue -> size--;
        return result;
    }
    return NULL;
}
