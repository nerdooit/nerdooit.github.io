#include <stdio.h>
#include<limits.h>
#define MAX 10

int perm[MAX];					/* 순열저장 배열 */
int used[MAX];					/* 순열 체크 배열 */
int wtime[MAX][MAX];              /* 개인별 해당 작업의 소요시간 저장 배열 */ 
int minV;                       /* 최소 작업시간 저장 */ 

void work(int n, int k);

int main(void)
{
	int T;
	freopen("data.txt", "r", stdin);
	scanf("%d", &T); // test case의 수 입력 받기
	for (int tc = 1; tc <= T; tc++)  // test case 수 만큼 반복
	{
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			used[i] = 0; // used 초기화
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &wtime[i][j]);
			}
		}
		minV = INT_MAX; //  minV = 100; - 문제의 조건에서 최대 100 이하로 정해도 됨 
		work(0, N);
		printf("%d\n", minV);
	}
}

/*----------------------------------------------------------------------
 * Function Name 	: work() - 순열 생성 및 작업시간 계산 함수
 * Argument 		: n - 순열 배열 저장 위치
 * 					  k - 배열 저장 인덱스 한계 값
 * Return value	: 없음
 ----------------------------------------------------------------------*/
void work(int n, int k)
{
	
	// TODO
	int i;
	if (n == k) {
		int s = 0;
		for (i = 0; i < k; i++) {
			s += wtime[perm[i]][i];
		}
		if (minV > s)
			minV = s;
	} else {
		for (i = 0; i < k; i++) {
			if (used[i] == 0) {
				used[i] = 1;
				perm[n] = i;
				work(n + 1, k);
				used[i] = 0;
			}
		}
	}
	
}






