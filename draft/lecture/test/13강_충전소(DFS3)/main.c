#include <stdio.h>

#define MAX 100
#define INF 1000
#define NAR -1

int station[MAX];
int sCnt;
int minV;

void dfs(int n, int energy, int c);

int main(void) {
	int i, j;
	int tc;

	freopen("data.txt", "rt", stdin);
	scanf("%d", &tc);
	
	for(i=1; i<=tc ; i++){
		minV = INF;
		scanf("%d", &sCnt);
		
		for (j=0 ; j<sCnt ; j++) {
			scanf("%d", &station[j]);
		}

		dfs(0, 0, 0);
		if (minV == INF) {
			printf("TC%d : %d\n", i, NAR);
		}
		else {
			printf("TC%d : %d\n", i, minV);
		}
	}
	return 0;
}
/*--------------------------------------------------------------------------------------
Function Name : dfs() - 충전회수를 깊이우선탐색(DFS) 하는 재귀함수 
Argument      : n - 탐색정점
                energy - 남은 에너지양 
                c - 현재까지의 충전 회수 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void dfs(int n, int energy, int c) {
	int i;

	// TODO

	if ( n >= (sCnt - 1) ) {
		if (c < minV) {
			minV = c;
		}
	}

	for (i = 1; i <= station[n]; i++) {
		dfs(n + i, energy - i, c + 1);
	}
}



