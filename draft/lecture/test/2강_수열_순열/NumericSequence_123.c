#include <stdio.h>
#define MAX 10
void printArray(int k);
int L[MAX];
int cnt=0;
void f(int n, int k) {
	int i;

    // TODO
	if (n == k) {
		cnt++;
		printArray(k);
	} else {
		for (i = 1; i <= k; i++) {
			L[n] = i;
			f(n+1, k);
		}
	}
}

int main(void) {
	f(0, 3);
	printf(" %d\n", cnt);
	return 0;
}
void printArray(int k){
	int i;
	for (i=0 ; i<k ; i++) {
		printf("%2d", L[i]);
	}
	printf("  ");
}

