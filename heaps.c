#include <stdio.h>
#include <stdlib.h>

/*
binary max heap yap�s� kullan�l�r. Bu yap�da her bir node'un etiketi �ocuklar�n�nkinden b�y�k e�ittir. Bu sayede en �ncelikli node root olur ve O(1) ile al�r�z.
Ancak root'u kullan�p ��kar�rsak tree yap�s� bozulur. Bunun i�in root ve herhangi bir leaf node'u swap yap�yoruz ve root'u o �ekilde siliyoruz. Bunu yapt�ktan 
sonra binary max heap yap�s�n� korumak i�in �u anki root �ocuklar�ndan k���k ise b�y�k olan �ocu�u ile swap yap�caz. Bunu bu node �ocuklar�ndan b�y�k e�it olana
kadar devam ettiricez. Buna sift down deniyor. En �ncelikliyi kullan�p silmeye ise extractMax deniyor. Bir di�er temel i�lem ise insert. Bunu yapmak i�inse insert
edice�imiz eleman� bir leaf'e ekliyoruz ve bu parent'�ndan k���k e�it olana kadar parent'�yla swap yap�yoruz. Buna da sift up deniyor. 

G�rd���n gibi t�m i�lemler a�ac�n boyu ile orant�l� karma��kl�kta. Bu sebeple a�ac� olabildi�ince k�sa yapmal�y�z. Bunu ise complete binary tree yaparak
sa�layabiliriz. complete binary tree, son seviyesi haricinde t�m seviyeleri dolu olan, yani her bir node'un iki �ocu�unun oldu�u son seviyesinde de dolu de�ilse
t�m node'lar�n soldan sa�a do�ru dizildi�i bir binary tree'dir. Bu sebeple y�ksekli�i en fazla log2(n) dir.

Elimizdeki heap'in complete kalmas�n� ise insert ve extractMax metodlar�n� daha spesifik kullanarak sa�layabiliriz. Mesela insert yaparken herhangi bir leaf'e
de�il de dolu olmayan en soldaki node'a ekleme yapar�z ve sift up'� kullan�r�z. extractMax i�in ise son seviyedeki herhangi bir node de�il de son seviyedeki en
sa� node ile root'u swap edip sonra sift down yapar�z.

Heap implemantasyonu tree kullan�larak de�il array kullan�larak yap�l�r. Bundaki sebep bir complete binary tree'nin arrayda tutulabilmesi �zelli�idir.
binary tree'de root'tan ba�layarak soldan sa�a do�ru 0 based index verdi�imizi d���n. i. node'un parent'� (i - 1) / 2). node iken �ocuklar� 2 * i + 1 ve 
2 * i + 2 'de bulunur. Bu sayede array'in sonuna yeni eleman ekledi�imizde complete �zelli�i bozmadan eklemi� oluyoruz.
*/

void print(int* heap, int n){
	int i;
	for(i=0;i<n;i++) printf("%d ", heap[i]);
	printf("\n");
}

void siftUp(int* heap, int i){
	int temp;
	while(i){
		if(heap[i] > heap[(i - 1) / 2]){
			temp = heap[i];
			heap[i] = heap[(i - 1) / 2];
			heap[(i - 1) / 2] = temp;
		}
		i = (i - 1) / 2;
	}
}

void siftDown(int* heap, int n, int i){
	int temp, index = i;
	
	do{
		//print(heap, n);
		i = index;
		if(2 * i + 1 < n && heap[2 * i + 1] > heap[index]){
			index = 2 * i + 1;
		}
		if(2 * i + 2 < n && heap[2 * i + 2] > heap[index]){
			index = 2 * i + 2;
		}
		temp = heap[i];
		heap[i] = heap[index];
		heap[index] = temp;
	} while(i != index);
}

//son seviyenin en soluna ekler. contradiction ile ispatlayabilirsin. Bu �ekilde complete'lik bozulmaz.
void insert(int* heap, int* n, int x){
	heap[*n] = x;
	siftUp(heap, *n);
	(*n)++;
}

//son seviyenin en sa��yla root'u swapler. contradiction ile ispatlayabilirsin. Bu �ekilde complete'lik bozulmaz.
int extractMax(int* heap, int* n){
	int result = heap[0];
	heap[0] = heap[*n - 1];
	(*n)--;
	siftDown(heap, *n, 0);
	return result;
}

int getMax(int* heap){
	return heap[0];
}

//O(n). ��nk� silece�imiz eleman� bulmam�z laz�m ve bunu t�m elemanlara bakarak yap�yoruz.
void removeElement(int* heap, int* n, int p){
	int i=0;
	while(i < *n && heap[i] != p) i++;
	if(i == *n) return;
	heap[i] = INT_MAX;
	siftUp(heap, i);
	extractMax(heap, n);
}

void changePriority(int* heap, int n, int i, int p){
	if(i >= n || heap[i] == p) return;
	int oldP = heap[i];
	heap[i] = p;
	if(p > oldP) siftUp(heap, i);
	else siftDown(heap, n, i);
}

int main(){
//	int heap[20] = {42,29,18,14,7,18,12,11,13}, n = 9, i;
	int heap[20], n = 0, i, x;
	scanf("%d", &n);
	for(i=0;i<n;i++){
		scanf("%d", &x);
		insert(heap, &n, x);
	}
	print(heap, n);
	changePriority(heap, n, 3, 5);
	print(heap, n);
//	removeElement(heap, &n, 7);
//	print(heap, n);
	return 0;
}
