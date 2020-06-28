#include<stdio.h>
#define MAX 1000
typedef enum { FALSE, TRUE } BOOL;
int a[MAX + 1];   // 순열 저장 배열 
BOOL check[MAX + 1];
void dfs(int x);  // 깊이우선 탐색 함수
int main()
{
	int tc, ti;  // 테스트 케이스 저장
	int n;   // 순열내의 숫자의 개수 저장
	int i;
	int ans;  // 순열내의 사이클의 개수 저장 

	freopen("data.txt", "rt", stdin);
	scanf("%d", &tc);

	// TODO
	for (ti = 1; ti <= tc; ti++) {
		scanf("%d", &n);
		for (i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			check[i] = FALSE;
		}
		ans = 0;

		for (i = 1; i <= n; i++) {
			if (check[i] == FALSE) {
				dfs(i);
				ans++;
			}
		}
		printf("TC%d : %d\n", ti, ans);
	}
	return 0;
}

void dfs(int x)
{
	// TODO
	if (check[x]) return;
	check[x] = TRUE;
	dfs(a[x]);
}

