#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//polynomial hashing for string keys
int polyHash(char* str, int i, int j, int p, int x){
	int hash = 0, k, n = strlen(str);
	
	for(k=j;k>=i;k--){
		hash = (hash * x + str[k]) % p;
	}
	
	return hash;
}

int areEquals(char* str1, int a, int b, char* str2, int c, int d){
	int i, n = b - a + 1;
	if(a > b || c > d || (a - b) != (c - d)) return 0;
	
	for(i=0;i<n;i++){
		if(str1[i] != str2[i]) return 0;
	}
	
	return 1;
}

void rabinKarps(char* T, char* P, int p, int x){
	int y = 1, i, k = 0, n = strlen(P), m = strlen(T);
	int* positions = (int*) malloc((m - n + 1) * sizeof(int));
	
	int hashP = polyHash(P, 0, n - 1, p, x);
	int hashSub = polyHash(T, m - n, m - 1, p, x);
	
	if(hashP == hashSub && areEquals(P, 0, n - 1, T, m - n, m - 1)){
		positions[k++] = m - n;
	}

	for(i=0;i<n;i++) y = (y * x) % p; //x^n % p
	
	for(i=m-n-1;i>=0;i--){
		hashSub = (hashSub * x + T[i] - (y * T[i + n]) % p) % p;

		if(hashP == hashSub && areEquals(P, 0, n - 1, T, i, i + n - 1)){
			positions[k++] = i;
		}
	}
	
	for(i=k-1;i>=0;i--){
		printf("%d ", positions[i]);
	}
}

int main(){
	int p = 997, x = 31;
	char T[100], P[20];
	printf("T: ");
	scanf("%s", T);
	printf("P: ");
	scanf("%s", P);
	rabinKarps(T, P, p, x);
	
	return 0;
}
