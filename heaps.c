#include <stdio.h>
#include <stdlib.h>

/*
binary max heap yapýsý kullanýlýr. Bu yapýda her bir node'un etiketi çocuklarýnýnkinden büyük eþittir. Bu sayede en öncelikli node root olur ve O(1) ile alýrýz.
Ancak root'u kullanýp çýkarýrsak tree yapýsý bozulur. Bunun için root ve herhangi bir leaf node'u swap yapýyoruz ve root'u o þekilde siliyoruz. Bunu yaptýktan 
sonra binary max heap yapýsýný korumak için þu anki root çocuklarýndan küçük ise büyük olan çocuðu ile swap yapýcaz. Bunu bu node çocuklarýndan büyük eþit olana
kadar devam ettiricez. Buna sift down deniyor. En öncelikliyi kullanýp silmeye ise extractMax deniyor. Bir diðer temel iþlem ise insert. Bunu yapmak içinse insert
ediceðimiz elemaný bir leaf'e ekliyoruz ve bu parent'ýndan küçük eþit olana kadar parent'ýyla swap yapýyoruz. Buna da sift up deniyor. 

Gördüðün gibi tüm iþlemler aðacýn boyu ile orantýlý karmaþýklýkta. Bu sebeple aðacý olabildiðince kýsa yapmalýyýz. Bunu ise complete binary tree yaparak
saðlayabiliriz. complete binary tree, son seviyesi haricinde tüm seviyeleri dolu olan, yani her bir node'un iki çocuðunun olduðu son seviyesinde de dolu deðilse
tüm node'larýn soldan saða doðru dizildiði bir binary tree'dir. Bu sebeple yüksekliði en fazla log2(n) dir.

Elimizdeki heap'in complete kalmasýný ise insert ve extractMax metodlarýný daha spesifik kullanarak saðlayabiliriz. Mesela insert yaparken herhangi bir leaf'e
deðil de dolu olmayan en soldaki node'a ekleme yaparýz ve sift up'ý kullanýrýz. extractMax için ise son seviyedeki herhangi bir node deðil de son seviyedeki en
sað node ile root'u swap edip sonra sift down yaparýz.

Heap implemantasyonu tree kullanýlarak deðil array kullanýlarak yapýlýr. Bundaki sebep bir complete binary tree'nin arrayda tutulabilmesi özelliðidir.
binary tree'de root'tan baþlayarak soldan saða doðru 0 based index verdiðimizi düþün. i. node'un parent'ý (i - 1) / 2). node iken çocuklarý 2 * i + 1 ve 
2 * i + 2 'de bulunur. Bu sayede array'in sonuna yeni eleman eklediðimizde complete özelliði bozmadan eklemiþ oluyoruz.
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

//son seviyenin en soluna ekler. contradiction ile ispatlayabilirsin. Bu þekilde complete'lik bozulmaz.
void insert(int* heap, int* n, int x){
	heap[*n] = x;
	siftUp(heap, *n);
	(*n)++;
}

//son seviyenin en saðýyla root'u swapler. contradiction ile ispatlayabilirsin. Bu þekilde complete'lik bozulmaz.
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

//O(n). çünkü sileceðimiz elemaný bulmamýz lazým ve bunu tüm elemanlara bakarak yapýyoruz.
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
