#include <stdio.h>
#define MAX 30

// d[n][0] n번째 자리가 0인 경우 d[n-1][1](앞자리가 1인 경우만 가능)
// d[n][1] n번째 자리가 1인 경우 d[n-1][0] + d[n-1][1](앞자리가 0, 1인 경우 모두 가능)

int main(void)
{
	int n;
	int d[MAX+1][2];
	int i;
	scanf("%d", &n);

	// TO DO
	d[1][0] = 0;
	d[1][1] = 1;

	for (i = 2; i <= n; i++) {
		d[i][0] = d[i-1][1];
		d[i][1] = d[i-1][0] + d[i-1][1];
	}

	printf("%d\n", d[n][0] + d[n][1]);

	return 0;
}

