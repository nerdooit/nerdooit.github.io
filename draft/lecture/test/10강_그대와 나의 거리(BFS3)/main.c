#include <stdio.h>
#define MAX 1000000

int queue[MAX + 1];
int visit[MAX + 1];
int front;
int rear;
int D[] = { -1, 1, 5, 10 };  //  이동 가능 거리 
void bfs(int me, int you);  //이동위치를 너비우선으로 탐색하는 함수 

int main(void) 
{
	int i;
	int tc;
	int start;
	int end;

	freopen("data.txt", "r", stdin);
	scanf("%d", &tc);
	for (i=1 ; i<=tc ; i++) {
		scanf("%d %d", &start, &end);
		bfs(start, end);
		printf("TC %d : %d\n", i, visit[end]);
	}
	return 0;
}
/*--------------------------------------------------------------------------------------
Function Name : bfs() - 이동위치를 너비우선으로 탐색하는 함수 
Argument      : me - 나의 위치 
                you - 그대의 위치 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void bfs(int me, int you) {

	// TODO
	int i, v, now;

	for (i=0; i <= MAX;i++) {
		visit[i] = 0;
	}

	front = rear = 0;

	queue[rear++] = me;
	visit[me] = 0;

	while (front != rear) {
		now = queue[front++];
		if (now == you) {
			break;
		}
		else {
			for (i = 0; i < (sizeof(D) / sizeof(D[0])); i++) {
				v = now + D[i];
				if ((v>0) && (v <= MAX) && (v != me) && (visit[v] == 0)) {
					visit[v] = visit[now] + 1;
					queue[rear++] = v;
				}
			}
		}
	}

}



