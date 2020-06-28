#include <stdio.h>
#define MAX 10
void printArray(int m);
int L[MAX];
int cnt;
void f(int n, int k, int m) {
	int i;

	// TODO
	if (n==m) {
		cnt++;
		printArray(m);
	} else {
		for (i=1; i<=k; i++) {
			L[n] = i;
			f(n + 1, k, m);
		}
	}
}
int main(void) {
	f(0, 5, 3);
	printf("%d\n", cnt);
	return 0;
}

void printArray(int m){
	int i;
	for (i=0 ; i<m ; i++) {
		printf("%2d", L[i]);
	}
	printf("\t");
}

