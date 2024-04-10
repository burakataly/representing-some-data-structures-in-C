#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int key;
	int height;
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
void BFS(NODE* root);
void push(QUEUE* queue, NODE* i);
NODE* pop(QUEUE* queue);
NODE* find(NODE* root, int key);
NODE* nextLargest(NODE* root, int key);
NODE* nextLargest2(NODE* node);
NODE* descendant(NODE* node);
NODE* ancestor(NODE* node);
void rangeSearch(int x, int y, NODE* root);
NODE* insertNode(NODE** root, int key);
NODE* insertToAVL(NODE** root, int key);
NODE* deleteNode(NODE** root, int key);
void deleteFromAVL(NODE** root, int key);
int getBalance(NODE* node);
void adjustHeight(NODE* node);
int height(NODE* node);
int max(int a, int b);
NODE* treeMax(NODE* root);
NODE* treeMin(NODE* root);
void rebalanceRight(NODE** root, NODE* node);
void rebalanceLeft(NODE** root, NODE* node);
void rotateRight(NODE** root, NODE* node);
void rotateLeft(NODE** root, NODE* node);
void rebalance(NODE** root, NODE* node);
NODE* merge(NODE* root1, NODE* root2);
void mergeWithRoot(NODE* root1, NODE* root2, NODE* temp);
NODE* AVLTreeMergeWithRoot(NODE* root1, NODE* root2, NODE* temp);
NODE* mergeWithNaiveWay(NODE* root1, NODE* root2);
void split(NODE* root, int x, NODE** root1, NODE** root2);

int main(){
	NODE* root1 = NULL, *root2 = NULL;
	int i;
	
	for(i=1;i<=10;i+=2){
		insertToAVL(&root1, i);
		BFS(root1);
	}
	
	for(i=2;i<=14;i+=2){
		insertToAVL(&root2, i);
		BFS(root2);
	}
	NODE* root = merge(root1, root2);
	BFS(root);
	insertToAVL(&root, 1);
	BFS(root);
	rangeSearch(5, 19, root);
/*	
	NODE* r1 = NULL, *r2 = NULL; 
	split(root, 1, &r1, &r2);
	
	BFS(r1);
	printf("\n");
	BFS(r2);
	printf("\n");
	
	
	deleteFromAVL(&root, 4);
	BFS(root);
	printf("\n");
	deleteFromAVL(&root, 7);
	BFS(root);
	printf("\n");
	deleteFromAVL(&root, 6);
	BFS(root);
	printf("\n");*/
	
	return 0;
}

NODE* createNode(int key){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node -> key = key;
	node -> height = 1;
	return node;
}

//bulamazsa en yakýn node'u döndürür.
NODE* find(NODE* root, int key){
	if(root == NULL) return NULL;
	if(root -> key == key) return root;
	if(root -> key > key) return (root -> left != NULL) ? find(root -> left, key) : root;
	if(root -> key < key) return (root -> right != NULL) ? find(root -> right, key) : root;
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

NODE* insertToAVL(NODE** root, int key){
	NODE* node = insertNode(root, key);
	rebalance(root, node);
	return node;
}

NODE* deleteNode(NODE** root, int key){
	NODE* node = find(*root, key);
	if(node == NULL) return NULL;
	
	if(node -> right == NULL){
		NODE* parent = node -> parent;
		if(node -> parent != NULL){
			if(node -> key > node -> parent -> key) node -> parent -> right = node -> left;
			else node -> parent -> left = node -> left;
		}
		else *root = node -> left;
		
		if(node -> left != NULL) node -> left -> parent = node -> parent;
		free(node);
		return parent;
	}
	else{
		NODE* next = nextLargest2(node);
		NODE* parent = next -> parent;
		if(next -> key > next -> parent -> key) next -> parent -> right = next -> right;
		else next -> parent -> left = next -> right;
		if(next -> right != NULL) next -> right -> parent = next -> parent;
		node -> key = next -> key;
		free(next);
		return parent;
	}
}

void deleteFromAVL(NODE** root, int key){
	NODE* parent = deleteNode(root, key);
	if(parent == NULL) return;
	rebalance(root, parent);
}

void rebalance(NODE** root, NODE* node){
	NODE* parent = node -> parent;
	int balance = getBalance(node);
	if(balance > 1){
		rebalanceRight(root, node);
	}
	if(balance < -1){
		rebalanceLeft(root, node);
	}
	adjustHeight(node);
	if(parent != NULL) rebalance(root, parent);
}

int getBalance(NODE* node){
	return height(node -> left) - height(node -> right);
}

void adjustHeight(NODE* node){
	if(node == NULL) return;
	node -> height = max(height(node -> left), height(node -> right)) + 1;
}

int height(NODE* node){
	return (node == NULL) ? 0 : node -> height;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

void rebalanceRight(NODE** root, NODE* node){
	NODE *temp = node -> left;
	if(temp == NULL) return;
	if(getBalance(temp) < 0) rotateLeft(root, temp);
	rotateRight(root, node);
	adjustHeight(node);
	adjustHeight(temp);
}

void rebalanceLeft(NODE** root, NODE* node){
	NODE *temp = node -> right;
	if(getBalance(temp) > 0) rotateRight(root, temp);
	rotateLeft(root, node);
	adjustHeight(node);
	adjustHeight(temp);
}

void rotateRight(NODE** root, NODE* node){
	NODE *temp = node -> left;
	
	temp -> parent = node -> parent;
	if(temp -> parent != NULL){
		if(temp->parent->left == node) temp -> parent -> left = temp;
		else temp -> parent -> right = temp;
	}
	else *root = temp;
	
	node -> left = temp->right;
	if(temp->right != NULL) temp->right->parent = node;
	
	temp -> right = node;
	node -> parent = temp;
}

void rotateLeft(NODE** root, NODE* node){
	NODE *temp = node->right;

	temp -> parent = node -> parent;
	if(temp -> parent != NULL){
		if(temp->parent->left == node) temp -> parent -> left = temp;
		else temp -> parent -> right = temp;
	}
	else *root = temp;
	
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

NODE* nextLargest(NODE* root, int key){
	NODE* found = find(root, key);
	if(found == NULL) return NULL;
	if(found -> right != NULL) return descendant(found -> right);
	else return ancestor(found);
}

NODE* nextLargest2(NODE* node){
	if(node == NULL) return NULL;
	if(node -> right != NULL) return descendant(node -> right);
	else return ancestor(node);
}

NODE* descendant(NODE* node){
	return (node -> left != NULL) ? descendant(node -> left) : node;
}

NODE* ancestor(NODE* node){
	if(node -> parent == NULL) return NULL;
	if(node -> key < node -> parent -> key) return node -> parent;
	return ancestor(node -> parent);
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

/*
iki tree için birincinin tüm nodelarý ikincininkilerden küçük olmalý. (bu þart, birleþtirme iþlemini iki treedeki
node sayýlarý toplamýndan daha iyi karmaþýklýkta yapmak için gerekli. Bu þart saðlanmazsa O(n+m) karmaþýklýkta
birleþtirme yapan bir fonksyion kullanýlabilir.)
*/
NODE* merge(NODE* root1, NODE* root2){
	if(root1 == NULL) return root2;
	if(root2 == NULL) return root1;
	NODE* max1 = treeMax(root1);
	NODE* min2 = treeMin(root2);
	
	if(max1 -> key > min2 -> key) return mergeWithNaiveWay(root1, root2);
	else{
		NODE* temp = createNode(max1 -> key);
		deleteFromAVL(&root1, max1 -> key);
		return AVLTreeMergeWithRoot(root1, root2, temp);		
	}
}

// complexity => O( |root1 -> height - root2 -> height| + 1 ) : Eðerki iki treenin yükseklikleri farký avl balance þartýný saðlýyosa O(1), saðlamýyorsa
// büyük olanda küçük olanýn yüksekliðiyle avl þartýný saðlayacak kadar aþaðý iniyoruz ve sonra O(1)'lik bir iþlem yapýyoruz.

NODE* AVLTreeMergeWithRoot(NODE* root1, NODE* root2, NODE* temp){
	if(abs(height(root1) - height(root2)) <= 1){
		mergeWithRoot(root1, root2, temp);
		adjustHeight(temp);
		return temp;
	}
	else if(height(root1) > height(root2)){
		NODE* root = root1;
		 
		while(abs(height(root1) - height(root2)) > 1){
			root1 = root1 -> right;
		}
		
		NODE* parent = root1 -> parent;
		
		mergeWithRoot(root1, root2, temp);
		
		temp -> parent = parent;
		parent -> right = temp;
		
		adjustHeight(temp);
		rebalance(&root, temp);
		
		return root;
	}
	else{
		NODE* root = root2;
		
		while(abs(height(root1) - height(root2)) > 1){
			root2 = root2 -> left;
		}
		NODE* parent = root2 -> parent;
		
		mergeWithRoot(root1, root2, temp);
		
		temp -> parent = parent;
		parent -> left = temp;
		
		adjustHeight(temp);
		rebalance(&root, temp);
		
		return root;
	}
}

void mergeWithRoot(NODE* root1, NODE* root2, NODE* temp){
	temp -> left = root1;
	temp -> right = root2;
	if(root1 != NULL) root1 -> parent = temp;
	if(root2 != NULL) root2 -> parent = temp;
}

NODE* mergeWithNaiveWay(NODE* root1, NODE* root2){
	while(root1 != NULL){
		insertToAVL(&root2, root1 -> key);
		deleteFromAVL(&root1, root1 -> key);
	}
	return root2;
}

void split(NODE* root, int x, NODE** root1, NODE** root2){

	if(root == NULL){
		*root1 = NULL;
		*root2 = NULL;
	}
	else if(root -> key == x){
		*root1 = root -> left;
		*root2 = root -> right;
		root->left->parent = NULL;
		root->right->parent = NULL;
		free(root);
	}
	else if(root -> key > x){
		split(root -> left, x, root1, root2);
		mergeWithRoot(*root2, root -> right, root);
		*root2 = root;
	}
	else{
		split(root -> right, x, root1, root2);
		mergeWithRoot(root -> left, *root1, root);
		*root1 = root;
	}
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
