#include <stdio.h>
#include "Dijkstra.h"

int G[MAX][MAX];	/* 그래프 배열 */
int V[MAX];			/* 노드 처리 체크 배열 */
int D[MAX];			/* 최단거리 저장 배열 */
int P[MAX];			/* 직전노드 저장 배열 */
int vertex;			/* 정점 수 저장 배열 */
int edge;			/* 간선 수 저장 배열 */
/*--------------------------------------------------------------------------------------
Function Name : dijkstra() - 전달된 정점으로 부터 나머지 정점까지의 최소 가중치를 계산하고 
                             경로를 연산함
Argument      : s - 선택된 정점 번호
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void dijkstra(int s) 
{
	/* distance와 predecessor, visited 배열 초기화 */
	int i;
	int j;

	// TODO
	for (i = 0; i < vertex; i++) {
		D[i] = G[s][i];
		V[i] = 0;

		if (G[s][i] != INF) {
			P[i] = s;
		} else {
			P[i] = NIL;
		}
	}

	V[s] = 1;
	for (i = 0; i < vertex; i++) {
		int minIndex = 0;
		int minValue = INF;
		for (j = 0; j < vertex; j++) {
			if ((V[j] == 0) && (D[j] < minValue)) {
				minIndex = j;
				minValue = D[j];
			}
		}
		V[minIndex] = 1;

		for (j = 0; j < vertex; j++) {
			if (V[j] == 0) {
				if ((D[minIndex] + G[minIndex][j]) < D[j]) {
					D[j] = D[minIndex] + G[minIndex][j];
					P[j] = minIndex;
				}
			}
		}
	}
} 
/*--------------------------------------------------------------------------------------
Function Name : printPredecessor() - 직전정점 저장 배열 출력 함수 
Argument      : 없음 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void printPredecessor(void) 
{
	int i;

	printf("[Predecessor]\n"); 
	for (i=0 ; i<vertex ; i++) {
		printf("%2c ", i + 'A');
	}
	printf("\n");

	for (i=0 ; i<vertex ; i++) {
		printf("%2c ", P[i] + 'A');
	}
	printf("\n");
}

/*--------------------------------------------------------------------------------------
Function Name : printPath() - 시작 정점->끝 정점까지의 path 및 가중치 출력
Argument      : s - 시작 정점 번호
			    t- 도착 정점 번호
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void printPath(int s, int t) 
{
	// TODO
	int stack[MAX] = {0,};
	int top = 0;

	stack[top++] = t;
	while (P[t] != s && P[t] != NIL) {
		t = P[t];
		stack[top++] = t;
	}

	if ( s == P[t] ) {
		printf("이동 경로 : %c -> ", s + 'A');
		while (top > 0) {
			printf("%c", stack[--top] + 'A');
			if (top > 0) {
				printf(" -> ");
			}
		}
		printf("\n");
	} else {
		printf("도달 불가능!!!\n");
	}
}
/*--------------------------------------------------------------------------------------
Function Name : printDistance() - 시작정점으로 부터 각 정점까지의 최소가중치를 
                                저장하고 있는 배열 출력 함수 
Argument      : s - 선택된 정점 번호
Return Valuse : 없음
--------------------------------------------------------------------------------------*/

void printDistance(int s) 
{
	int i;
	printf("[Distance]\n"); 
	printf("%c > ", s + 'A');
	for (i=0 ; i<vertex ; i++) {
		printf("%2c", i + 'A');
	}
	printf("\n");

	printf("    ");
	for (i=0 ; i<vertex ; i++) {
		if (D[i] == INF) {
			printf("%2c", 'x');
		}
		else {
			printf("%2d", D[i]);
		}
	}
	printf("\n");
}
/*--------------------------------------------------------------------------------------
Function Name : initGraph() - 그래프 데이터를 읽어들여 인접행열 생성 
Argument      : 없음 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void initGraph(void) 
{
	int i, j, w;

	// TODO
	char v1, v2;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (i == j) G[i][j] = 0;
			else G[i][j] = INF;
		}
	}

	scanf("%d %d", &vertex, &edge);
	for (i = 0; i < edge; i++) {
		scanf(" %c %c %d", &v1, &v2, &w);
		G[v1 - 'A'][v2 - 'A'] = w;
		G[v2 - 'A'][v1 - 'A'] = w;
	}

}
/*--------------------------------------------------------------------------------------
Function Name : printGraph() - 그래프 인접행열 출력 
Argument      : 없음 
Return Valuse : 없음
--------------------------------------------------------------------------------------*/
void printGraph(void) 
{
	int i;
	int j;
	printf("[Print Graph]\n"); 
	printf("%3s", "");
	for (i=0 ; i<vertex ; i++) {
		printf("%3c", 'A' + i);
	}
	printf("\n");

	for (i=0 ; i<vertex ; i++) {
		printf("%3c", 'A' + i);
		for (j=0 ; j<vertex ; j++) {
			if (G[i][j] == INF) {
				printf("%3s", "∞");
			}
			else {
				printf("%3d", G[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}



