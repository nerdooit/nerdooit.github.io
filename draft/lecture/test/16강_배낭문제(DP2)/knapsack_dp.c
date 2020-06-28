#include <stdio.h>
#define MAX_CNT 10       // 물건의 최대개수
#define MAX_WEIGHT 1000  // 최대 무게
int w[MAX_CNT+1];  // 물건의 무게를 저장하는 배열 (0번방 사용 안함)
int v[MAX_CNT+1];  // 물건별 가치를 저장하는 배열 (0번방 사용 안함)
int n;             // 물건의 개수 저장변수
int maxW;          // 배낭에 저장 가능한 최대 무게
void dataLoad();
int knapsack(int i, int r);
int D[MAX_CNT+1][MAX_WEIGHT+1];
int main()
{
	int i,j;
	int tc, ti;
	
	freopen("knapsack.txt", "rt", stdin);
	scanf("%d", &tc);
	for(ti=1; ti<=tc; ti++){
		dataLoad();
		//Dynamic Table 값 채우기

		// TO DO
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= maxW; ++j) {
				if(w[i] > j) {
					D[i][j] = D[i-1][j];
				} else {
					D[i][j] = (D[i-1][j] > D[i-1][j-w[i]] + v[i]) ? D[i-1][j] : D[i-1][j-w[i]] + v[i];
				}
			}
		}

		printf("TC%d 최대 가치(DP) : %d\n", ti, D[n][maxW]);
		printf("TC%d 최대 가치(Re) : %d\n\n", ti, knapsack(1,maxW));
	}
	return 0;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: dataLoad() - 물건의 정보(무게, 가치)를 입력 받아 초기화하는 함수
--------------------------------------------------------------------------------------*/
void dataLoad()
{
	int i; /* iterator */

	scanf("%d %d", &n, &maxW);  /* 물건의 개수와 배낭에 저장가능한 최대무게 입력 */
	for(i=1; i<=n; ++i){
		scanf("%d %d", &w[i], &v[i]); /* 물건의 무게와 가치 입력 */
	}
	return;
}
/*------------------------------------------------------------------
함수명 및 기능: knapsack() - 해당하는 번호의 물건을 넣을 경우와 넣지 않을 경우 중 더 큰 가치를 리턴하는 재귀함수
전달인자 : i - 물건의 번호
        r - 남은 무게
리턴값: 해당물건을 넣은 경우의 가치와 넣지 않은 경우의 가치 중 큰 값
------------------------------------------------------------------*/
int knapsack(int i, int r)
{
	// TO DO
	int res1, res2;
	if (i == n+1) {
		return 0;
	} else if (r < w[i]) {
		return knapsack(i+1, r);
	} else {
		res1 = knapsack(i+1, r);
		res2 = knapsack(i+1, r-w[i]) + v[i];
		return (res1 > res2) ? res1 : res2;
	}
}



