#include <stdio.h>
#define MAX 100
int main(void)
{
	int N; // N개의 조
	int d[MAX+1][3] = {0, }; // d[i][j] : i조가 j색상을 골랐을 때 최소 합계 비용
	int w[MAX+1][3] = {0, }; // w[i][j] : i조가 j색상으로 인쇄할 때의 비용
	int i;
	int minCost;
	int tc, ti;
	freopen("posterData.txt", "rt", stdin);
	scanf("%d", &tc);
	for(ti=1; ti<=tc; ti++){
		scanf("%d", &N);
		
		// TO DO
		for ( i = 1; i <= N; i++ ) {
			scanf( "%d %d %d", &w[i][0], &w[i][1], &w[i][2] );
		}

		d[1][0] = w[1][0];
		d[1][1] = w[1][1];
		d[1][2] = w[1][2];

		for (i = 2; i<= N; i++) {
			d[i][0] = ((d[i-1][1] < d[i-1][2]) ? (d[i-1][1]) : (d[i-1][2])) + w[i][0];
			d[i][1] = ((d[i-1][0] < d[i-1][2]) ? (d[i-1][0]) : (d[i-1][2])) + w[i][1];
			d[i][2] = ((d[i-1][0] < d[i-1][1]) ? (d[i-1][0]) : (d[i-1][1])) + w[i][2];
		}

		minCost = (d[N][0] < d[N][1]) ? d[N][0]:d[N][1];
		minCost = (minCost<d[N][2]) ? minCost : d[N][2];

		printf("TC %d : %d\n", ti, minCost);
	}
	return 0;
}

