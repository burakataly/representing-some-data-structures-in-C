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
NODE* find(NODE* root, int key);
NODE* sFind(NODE* root, int key);
NODE* insertNode(NODE** root, int key);
void insertToST(NODE** root, int key);
void deleteFromST(NODE** root, int key);
void split(NODE* root, int key, NODE** root1, NODE** root2);
NODE* merge(NODE* root1, NODE* root2);
NODE* splay(NODE* node);
void rotateRight(NODE* node);
void rotateLeft(NODE* node);
NODE* treeMax(NODE* root);
NODE* treeMin(NODE* root);
void BFS(NODE* root);
void push(QUEUE* queue, NODE* i);
NODE* pop(QUEUE* queue);

int main(){
	NODE* root = NULL;
	insertToST(&root, 1);
	BFS(root);
	insertToST(&root, 8);
	BFS(root);
	insertToST(&root, 5);
	BFS(root);
	insertToST(&root, 3);
	BFS(root);
	insertToST(&root, 7);
	BFS(root);
	insertToST(&root, 10);
	BFS(root);
	NODE *root1 = NULL, *root2 = NULL;
	split(root, 7, &root1, &root2);
	BFS(root1);
	BFS(root2);
	root = merge(root1, root2);
	BFS(root);
	deleteFromST(&root, 5);
	BFS(root);
	return 0;
}

NODE* createNode(int key){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node -> key = key;
	return node;
}

NODE* find(NODE* root, int key){
	if(root == NULL) return NULL;
	if(root -> key == key) return root;
	if(root -> key > key) return (root -> left != NULL) ? find(root -> left, key) : root;
	if(root -> key < key) return (root -> right != NULL) ? find(root -> right, key) : root;
}

NODE* sFind(NODE* root, int key){
	NODE* node = find(root, key);
	splay(node);
	return node;
}

NODE* insertNode(NODE** root, int key){
	NODE* node = find(*root, key);
	if(node == NULL){
		*root = createNode(key);
		return *root;
	}
	if(node->key == key && node->left != NULL){
		NODE* temp = treeMax(node->left);
		temp->right = createNode(key);
		temp->right->parent = temp;
		return temp->right;
	}
	if(node -> key >= key){
		node -> left = createNode(key);
		node -> left -> parent = node; //parent'ýný ekleme ihityacý varsa diye
		return node -> left;
	}
	if(node -> key < key){
		node -> right = createNode(key);
		node -> right -> parent = node;
		return node -> right;
	}
}

void insertToST(NODE** root, int key){
	NODE* node = insertNode(root, key);
	splay(node);
	*root = node;
}

void deleteFromST(NODE** root, int key){
	NODE* node = sFind(*root, key);
	if(node == NULL || node->key != key){
		*root = node;
		return;
	}
	if(node->left != NULL) node->left->parent = NULL;
	if(node->right != NULL) node->right->parent = NULL;
	*root = merge(node->left, node->right);
	free(node);
}

void split(NODE* root, int key, NODE** root1, NODE** root2){
	if(root == NULL){
		*root1 = NULL;
		*root2 = NULL;
		return;
	}
	NODE* node = sFind(root, key);
	if(node->key == key){
		*root1 = node->left;
		*root2 = node->right;
		if(node->left != NULL) node->left->parent = NULL;
		if(node->right != NULL) node->right->parent = NULL;
		free(node);
	}
	else if(node->key > key){
		*root1 = node->left;
		*root2 = node;
		if(node->left != NULL) node->left->parent = NULL;
		node->left = NULL;
	}
	else{
		*root1 = node;
		*root2 = node->right;
		if(node->right != NULL) node->right->parent = NULL;
		node->right = NULL;
	}
}

NODE* merge(NODE* root1, NODE* root2){
	if(root1 == NULL) return root2;
	if(root2 == NULL) return root1;
	NODE* max1 = treeMax(root1);
	NODE* min2 = treeMin(root2);
	
	if(max1 -> key > min2 -> key) return NULL;
	else{
		splay(max1);
		max1->right = root2;
		root2->parent = max1;
		return max1;		
	}
}

NODE* treeMax(NODE* root){
	if(root == NULL) return NULL;
	while(root->right != NULL) root = root -> right;
	return root;
}

NODE* treeMin(NODE* root){
	if(root == NULL) return NULL;
	while(root -> left != NULL) root = root -> left;
	return root;
}

//the given node is going to be root after this function
NODE* splay(NODE* node){
	if(node == NULL) return NULL;
	//zig = rightRotate, zag = leftRotate
	while(node->parent != NULL){		
		if(node->parent->parent == NULL){ //zig or zag
			(node->parent->left == node) ? rotateRight(node->parent) : rotateLeft(node->parent);
		}
		else if(node->parent->left == node){
			if(node->parent->parent->left == node->parent){ //zig-zig
				rotateRight(node->parent->parent);
				rotateRight(node->parent);
			}
			else{ //zag-zig
				rotateRight(node->parent);
				rotateLeft(node->parent);
			}
		}
		else{
			if(node->parent->parent->right == node->parent){ //zag-zag
				rotateLeft(node->parent->parent);
				rotateLeft(node->parent);
			}
			else{ //zig-zag
				rotateLeft(node->parent);
				rotateRight(node->parent);
			}
		}
	}
	return node;
}

void rotateRight(NODE* node){
	NODE *temp = node -> left;
	
	temp -> parent = node -> parent;
	if(temp -> parent != NULL){
		if(temp->parent->left == node) temp -> parent -> left = temp;
		else temp -> parent -> right = temp;
	}
	
	node -> left = temp->right;
	if(temp->right != NULL) temp->right->parent = node;
	
	temp -> right = node;
	node -> parent = temp;
}

void rotateLeft(NODE* node){
	NODE *temp = node->right;
	
	temp -> parent = node -> parent;
	if(temp -> parent != NULL){
		if(temp->parent->left == node) temp -> parent -> left = temp;
		else temp -> parent -> right = temp;
	}
	
	node->right = temp->left;
	if(temp->left != NULL) temp->left->parent = node;
	
	temp -> left = node;
	node -> parent = temp;
}

void BFS(NODE* root){
	if(root == NULL) return;
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
